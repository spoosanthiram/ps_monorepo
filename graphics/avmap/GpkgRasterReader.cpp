#include "GpkgRasterReader.h"

#include <gdal/gdal_priv.h>
#include <spdlog/spdlog.h>

namespace Ps::Graphics {

constexpr auto kTile_Pixel = 256;

GpkgRasterReader::GpkgRasterReader(const std::shared_ptr<GpkgMapList::MapInfo>& map_info)
    : map_info_{map_info}
{
    raster_band_ = map_info_->raster_dataset->GetRasterBand(1);
    pixel_per_meter_ = 1.0 / map_info_->meter_per_pixel;
    SPDLOG_WARN("pixel_per_meter_: {}", pixel_per_meter_);
    tile_meter_ = kTile_Pixel * map_info_->meter_per_pixel;
    SPDLOG_WARN("tile_meter_: {}", tile_meter_);
    tile_id_max_ = Point2i{raster_band_->GetXSize() / kTile_Pixel, raster_band_->GetYSize() / kTile_Pixel};
    SPDLOG_WARN("tile_id_max_: ({}, {})", tile_id_max_[0], tile_id_max_[1]);
}

Point2i GpkgRasterReader::get_center_tile_id(const Point2d& center)
{
    const auto tile_id = Point2d{(center[0] - map_info_->top_left[0]) / tile_meter_,
                                 -(center[1] - map_info_->top_left[1]) / tile_meter_};
    SPDLOG_WARN("Tile Id: ({}, {})", tile_id[0], tile_id[1]);
    return Point2i{static_cast<int>(std::round(tile_id[0])), static_cast<int>(std::round(tile_id[1]))};
}

Point2i clamp(const Point2i& point, int32_t delta, const Point2i& high)
{
    return Point2i{std::clamp(point[0] + delta, 0, high[0]), std::clamp(point[1] + delta, 0, high[1])};
}

std::set<std::pair<int32_t, int32_t>> GpkgRasterReader::get_tile_ids(const Point2i& tile_id, int32_t dist_from_tile_id)
{
    const auto tile0 = clamp(tile_id, -dist_from_tile_id, tile_id_max_);
    SPDLOG_WARN("Tile 0: ({}, {})", tile0[0], tile0[1]);
    const auto tile1 = clamp(tile_id, +dist_from_tile_id, tile_id_max_);
    SPDLOG_WARN("Tile 1: ({}, {})", tile1[0], tile1[1]);
    std::set<std::pair<int32_t, int32_t>> tile_ids;
    for (int32_t x = tile0.x(); x < tile1.x(); ++x) {
        for (int32_t y = tile0.y(); y < tile1.y(); ++y) {
            tile_ids.emplace(x, y);
        }
    }
    return tile_ids;
}

GpkgRasterReader::Tile GpkgRasterReader::get_tile(const Point2i& tile_id)
{
    Tile tile;
    tile.tile_meter = tile_meter_;
    tile.tile_pixel = kTile_Pixel;
    tile.translation = Point2d{map_info_->top_left[0] + tile_id[0] * tile_meter_,
                               map_info_->top_left[1] - (tile_id[1] + 1) * tile_meter_};
    tile.buffer.resize(tile.tile_pixel * tile.tile_pixel);
    const auto cpl_err = raster_band_->RasterIO(GF_Read,
                                                tile_id[0] * kTile_Pixel,
                                                tile_id[1] * kTile_Pixel,
                                                tile.tile_pixel,
                                                tile.tile_pixel,
                                                tile.buffer.data(),
                                                tile.tile_pixel,
                                                tile.tile_pixel,
                                                GDT_Byte,
                                                0,
                                                0);
    if (cpl_err != CE_None) {
        SPDLOG_ERROR("Raster IO failed for tile: ({}, {})", tile_id[0], tile_id[1]);
        tile.buffer.clear();
    }
    return tile;
}

}  // namespace Ps::Graphics
