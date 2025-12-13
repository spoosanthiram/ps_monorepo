#pragma once

#include "GpkgMapList.h"

#include <set>

class GDALRasterBand;

namespace Ps::Graphics {

class GpkgRasterReader
{
public:
    struct Tile {
        double tile_meter{0.0};
        int tile_pixel{0};
        Point2d translation;
        std::vector<uint8_t> buffer;
    };

public:
    GpkgRasterReader(const std::shared_ptr<GpkgMapList::MapInfo>& map_info);

    Point2i get_center_tile_id(const Point2d& center);
    std::set<std::pair<int32_t, int32_t>> get_tile_ids(const Point2i& tile_id, int32_t dist_from_tile_id);
    Tile get_tile(const Point2i& tile_id);

private:
    std::shared_ptr<GpkgMapList::MapInfo> map_info_;
    GDALRasterBand* raster_band_{nullptr};
    double pixel_per_meter_{0.0};
    double tile_meter_{0.0};
    Point2i tile_id_max_;
};

}  // namespace Ps::Graphics
