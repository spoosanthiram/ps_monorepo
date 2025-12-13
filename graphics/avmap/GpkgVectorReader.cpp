#include "GpkgVectorReader.h"

#include <gdal/ogrsf_frmts.h>
#include <spdlog/spdlog.h>

namespace Ps::Graphics {

GpkgVectorReader::GpkgVectorReader(const std::shared_ptr<GpkgMapList::MapInfo>& map_info)
    : map_info_{map_info}
    , proj_{map_info->epsg}
{
    const auto& dataset = map_info_->vector_dataset;
    if (const auto meta_table = dataset->GetLayerByName("meta")) {
        auto meta_row = meta_table->GetNextFeature();
        while (meta_row != nullptr) {
            const std::string key = meta_row->GetFieldAsString("key");
            if (key == "X-map_cli-version") {
                std::string version_string = meta_row->GetFieldAsString("value");
                map_cli_major_version_ = std::stoi(version_string);
            }
            meta_row = meta_table->GetNextFeature();
        }
    }
}

std::vector<GpkgVectorReader::Polygon> GpkgVectorReader::get_polygons(const std::string& layer_name)
{
    std::vector<Polygon> result;

    const auto layer = map_info_->vector_dataset->GetLayerByName(layer_name.c_str());
    if (layer == nullptr || layer->GetGeomType() != wkbPolygon) {
        SPDLOG_WARN("Layer {} is not available or it's type not polygon");
        return result;
    }

    layer->ResetReading();
    while (auto feature = layer->GetNextFeature()) {
        auto polygon = get_polygon(feature);
        if (!polygon.rings.empty()) {
            result.emplace_back(std::move(polygon));
        }
        OGRFeature::DestroyFeature(feature);
    }

    return result;
}

GpkgVectorReader::Polygon GpkgVectorReader::get_polygon(OGRFeature* feature)
{
    Polygon polygon;

    auto geometry_ref = feature->GetGeometryRef();
    auto ogr_polygon = dynamic_cast<OGRPolygon*>(geometry_ref);
    if (ogr_polygon == nullptr) {
        SPDLOG_WARN("{} is not a polygon", feature->GetFID());
        return polygon;
    }

    if (auto ogr_ring = ogr_polygon->getExteriorRing()) {
        if (const auto size = ogr_ring->getNumPoints(); size > 2) {
            polygon.ogr_feature = feature;
            const auto iter = ogr_ring->getPointIterator();
            std::vector<std::array<float, 2>> ring;
            OGRPoint pos;
            for (int64_t i = 0; i < size; ++i) {
                iter->getNextPoint(&pos);
                const auto point = to_local_point(pos);
                if (i == 0) {
                    polygon.translation = point;
                }
                ring.emplace_back(std::array<float, 2>{static_cast<float>(point.x() - polygon.translation.x()),
                                                       static_cast<float>(point.y() - polygon.translation.y())});
            }
            polygon.rings.emplace_back(std::move(ring));
        }
    }

    return polygon;
}

Point2d GpkgVectorReader::to_local_point(const OGRPoint& pos)
{
    // Latitude: Y
    // Longitude: X
    return proj_.get_xy_from_latlon(
        GeoLocation{units::angle::degree_t{pos.getY()}, units::angle::degree_t{pos.getX()}});
}

}  // namespace Ps::Graphics
