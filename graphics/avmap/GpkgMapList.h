#pragma once

#include "GeoLocation.h"

#include "core/utils/ClassHelper.h"
#include "graphics/geometry/GraphicsGeometry.h"

#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Forward declaration for GDAL classes
class GDALDataset;

namespace Ps::Graphics {

class GdalDatasetDeleter
{
public:
    void operator()(GDALDataset* dataset) const;
};
using ScopedGdalDataset = std::unique_ptr<GDALDataset, GdalDatasetDeleter>;

ScopedGdalDataset open_gdal(const std::string& path);
ScopedGdalDataset open_gdal_ex(const std::string& path);

class GpkgMapList
{
public:
    struct MapInfo
    {
        MapInfo() = default;
        ~MapInfo() = default;

        MOVE_CONSTRUCTOR(MapInfo) = default;
        MOVE_ASSIGNMENT(MapInfo) = default;

        COPY_CONSTRUCTOR(MapInfo) = delete;
        COPY_ASSIGNMENT(MapInfo) = delete;

        std::filesystem::path gpkg_path;

        ScopedGdalDataset raster_dataset;
        Point2d top_left{0.0, 0.0};
        double meter_per_pixel{0.0};
        Point2d raster_center{0.0, 0.0};
        int32_t epsg{0};
        int32_t no_data_value{0};

        ScopedGdalDataset vector_dataset;
        GeoLocation geo_loc;
        Point2d vector_center{0.0, 0.0};
    };

public:
    GpkgMapList();
    ~GpkgMapList() = default;

    COPY_CONSTRUCTOR(GpkgMapList) = delete;
    MOVE_CONSTRUCTOR(GpkgMapList) = delete;
    COPY_ASSIGNMENT(GpkgMapList) = delete;
    MOVE_ASSIGNMENT(GpkgMapList) = delete;

    const std::vector<std::string>& get_map_names() const { return map_names_; }
    std::shared_ptr<MapInfo> get_map_info(const std::string& map_name) const;

private:
    void process_map_dir(const std::filesystem::path& map_dir);

    void fill_transform(std::shared_ptr<MapInfo>& map_info);
    void fill_raster_center(std::shared_ptr<MapInfo>& map_info);
    void fill_epsg(std::shared_ptr<MapInfo>& map_info);
    void fill_no_data_value(std::shared_ptr<MapInfo>& map_info);

    void fill_vector_info(std::shared_ptr<MapInfo>& map_info);
    std::optional<GeoLocation> parse_geo_location_from_metadata(std::shared_ptr<MapInfo>& map_info);

private:
    std::map<std::string, std::shared_ptr<MapInfo>> map_info_list_;
    std::vector<std::string> map_names_;
};

}  // namespace Ps::Graphics
