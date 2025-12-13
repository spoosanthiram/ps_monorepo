#include "GpkgMapList.h"

#include "CoordProjection.h"

#include <gdal/gdal_priv.h>
#include <gdal/ogrsf_frmts.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include <fstream>

namespace fs = std::filesystem;

namespace {

bool registeredGdal = false;

void register_gdal()
{
    if (!registeredGdal) {
        GDALAllRegister();
        registeredGdal = true;
    }
}

}  // namespace

namespace Ps::Graphics {

void GdalDatasetDeleter::operator()(GDALDataset* dataset) const
{
    GDALClose(dataset);
}

ScopedGdalDataset open_gdal(const std::string& path)
{
    return ScopedGdalDataset{static_cast<GDALDataset*>(GDALOpen(path.c_str(), GDALAccess::GA_ReadOnly))};
}

ScopedGdalDataset open_gdal_ex(const std::string& path)
{
    return ScopedGdalDataset{
        static_cast<GDALDataset*>(GDALOpenEx(path.c_str(), GDAL_OF_ALL, nullptr, nullptr, nullptr))};
}

GpkgMapList::GpkgMapList()
{
    register_gdal();

    fs::path maps_dir{"graphics/data/maps"};
    for (const auto& dir_entry : fs::directory_iterator{maps_dir}) {
        process_map_dir(dir_entry);
    }

    // fill sorted map names
    for (const auto& [name, v] : map_info_list_) {
        map_names_.push_back(name);
    }
}

std::shared_ptr<GpkgMapList::MapInfo> GpkgMapList::get_map_info(const std::string& map_name) const
{
    auto it = map_info_list_.find(map_name);
    if (it != map_info_list_.end()) {
        return it->second;
    }
    return std::shared_ptr<MapInfo>{};
}

void GpkgMapList::process_map_dir(const fs::path& map_dir)
{
    if (!fs::exists(map_dir) || !fs::is_directory(map_dir)) {
        return;
    }

    SPDLOG_INFO("Processing Map Dir: {}", map_dir.string());

    const auto map_name = map_dir.stem().string();

    for (const auto& dir_entry : fs::directory_iterator{map_dir}) {
        if (!dir_entry.is_regular_file() || dir_entry.path().extension() != ".gpkg") {
            return;
        }

        auto raster_dataset = open_gdal("GPKG:" + dir_entry.path().string() + "::Occupancy");
        auto vector_dataset = open_gdal_ex(dir_entry.path().string());

        if (raster_dataset && (vector_dataset && vector_dataset->GetLayerCount() > 0 &&
                               vector_dataset->GetLayerByName("dubins_nodes") != nullptr)) {
            // create MapInfo & fill it
            auto map_info = std::make_shared<MapInfo>();
            map_info->gpkg_path = dir_entry.path();
            map_info->raster_dataset = std::move(raster_dataset);
            map_info->vector_dataset = std::move(vector_dataset);

            try {
                fill_transform(map_info);
                fill_raster_center(map_info);
                fill_epsg(map_info);
                fill_no_data_value(map_info);
                fill_vector_info(map_info);
            }
            catch (std::exception& err) {
                SPDLOG_ERROR("Failed to get info for {}, Error: {}", map_dir.string(), err.what());
                continue;
            }

            map_info_list_[map_name] = map_info;
        }
    }
}

void GpkgMapList::fill_transform(std::shared_ptr<MapInfo>& map_info)
{
    std::array<double, 6> transform;
    // transform[0] /* top left x */
    // transform[1] /* w-e pixel resolution */
    // transform[2] /* 0 */
    // transform[3] /* top left y */
    // transform[4] /* 0 */
    // transform[5] /* n-s pixel resolution (negative value) */
    map_info->raster_dataset->GetGeoTransform(transform.data());
    if (transform[1] <= 0 || transform[1] != -transform[5] || transform[2] != 0 || transform[4] != 0) {
        throw std::runtime_error{"Incorect Map Transform"};
    }

    map_info->top_left[0] = transform[0];
    map_info->top_left[1] = transform[3];

    map_info->meter_per_pixel = transform[1];
}

void GpkgMapList::fill_raster_center(std::shared_ptr<MapInfo>& map_info)
{
    const auto band = map_info->raster_dataset->GetRasterBand(1);
    if (band == nullptr) {
        std::runtime_error{"No raster band available."};
    }

    Point2d raster_size{band->GetXSize() * map_info->meter_per_pixel, band->GetYSize() * map_info->meter_per_pixel};
    SPDLOG_DEBUG("Raster size: {}, {}", raster_size.x(), raster_size.y());

    Point2d bottom_right{map_info->top_left.x() + raster_size.x(), map_info->top_left.y() - raster_size.y()};
    map_info->raster_center = (map_info->top_left + bottom_right) * 0.5;
}

void GpkgMapList::fill_epsg(std::shared_ptr<MapInfo>& map_info)
{
    const auto proj_ref = map_info->raster_dataset->GetProjectionRef();
    if (proj_ref == nullptr) {
        std::runtime_error{"Couldn't get projection ref"};
    }
    OGRSpatialReference spatial_ref;
    if (spatial_ref.importFromWkt(proj_ref) != OGRERR_NONE) {
        std::runtime_error{"Couldn't import projection ref"};
    }
    const auto ref_root = spatial_ref.GetRoot();
    if (ref_root == nullptr) {
        std::runtime_error{"Spatial reference error"};
    }
    const auto ref_root_value = ref_root->GetValue();
    if (ref_root_value == nullptr || ref_root_value != std::string_view{"PROJCS"}) {
        std::runtime_error{"Spatial reference error"};
    }
    const auto authority = ref_root->GetNode("AUTHORITY");
    if (authority == nullptr || authority->GetChildCount() != 2) {
        std::runtime_error{"No AUTHORITY"};
    }
    const auto child0 = authority->GetChild(0);
    const auto child1 = authority->GetChild(1);
    if (child0 == nullptr || child1 == nullptr) {
        std::runtime_error{"No EPSG"};
    }
    const auto child0_value = child0->GetValue();
    const auto child1_value = child1->GetValue();
    if (child0_value == nullptr || child0_value != std::string_view{"EPSG"} || child1_value == nullptr) {
        std::runtime_error{"No EPSG"};
    }
    map_info->epsg = std::stoi(child1_value);
}

void GpkgMapList::fill_no_data_value(std::shared_ptr<MapInfo>& map_info)
{
    const auto value = CPLStringList{map_info->raster_dataset->GetMetadata(), FALSE}["no-data-value"];
    map_info->no_data_value = (value == nullptr) ? 255 : std::stoi(value);
}

void GpkgMapList::fill_vector_info(std::shared_ptr<MapInfo>& map_info)
{
    auto geo_loc = parse_geo_location_from_metadata(map_info);
    if (!geo_loc) {
        const auto layer = map_info->vector_dataset->GetLayerByName("dubins_nodes");
        OGREnvelope envelope;
        const auto err = layer->GetExtent(&envelope);
        if (err != OGRERR_NONE) {
            throw std::runtime_error{"Could not get extents for Geo Position"};
        }
        geo_loc = GeoLocation{units::angle::degree_t{(envelope.MinY + envelope.MaxY) / 2.0},
                              units::angle::degree_t{(envelope.MinX + envelope.MaxX) / 2.0}};
    }

    map_info->geo_loc = geo_loc.value();

    CoordProjection coord_proj{map_info->epsg};
    map_info->vector_center = coord_proj.get_xy_from_latlon(map_info->geo_loc);
}

std::optional<GeoLocation> GpkgMapList::parse_geo_location_from_metadata(std::shared_ptr<MapInfo>& map_info)
{
    const auto metadata_path = map_info->gpkg_path.parent_path() / "metadata.json";

    std::ifstream metadat_stream{metadata_path};
    if (!metadat_stream.is_open()) {
        SPDLOG_WARN("Could not open {}", metadata_path.string());
        return std::nullopt;
    }

    nlohmann::json metadata_json;
    try {
        metadat_stream >> metadata_json;
    }
    catch (std::exception& err) {
        SPDLOG_WARN("Could not parse {} as JSON", metadata_path.string());
        return std::nullopt;
    }

    try {
        const auto bbox_json = metadata_json.at("location").at("boundingBox");
        const auto min_json = bbox_json.at("min");
        const auto min_lat = min_json.at("lat").get<double>();
        const auto min_lng = min_json.at("lng").get<double>();
        const auto max_json = bbox_json.at("max");
        const auto max_lat = max_json.at("lat").get<double>();
        const auto max_lng = max_json.at("lng").get<double>();
        return GeoLocation{units::angle::degree_t{(min_lat + max_lat) / 2.0},
                           units::angle::degree_t{(min_lng + max_lng) / 2.0}};
    }
    catch (std::exception& err) {
        SPDLOG_WARN("Could not get location from {}, Error: {}", metadata_path.string(), err.what());
    }

    return std::nullopt;
}

}  // namespace Ps::Graphics
