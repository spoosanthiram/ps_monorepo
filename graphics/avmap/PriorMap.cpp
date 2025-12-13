#include "PriorMap.h"

#include <mapbox/earcut.hpp>
#include <spdlog/spdlog.h>

///
///
///

// #include <gdal/gdal_priv.h>

// #include <iostream>

namespace Ps::Graphics {

PriorMap::PriorMap(const std::shared_ptr<GpkgMapList::MapInfo>& map_info)
    : map_info_{map_info}
    , vector_reader_{map_info_}
    , raster_reader_{map_info_}
{}

GraphicsGeometry PriorMap::get_segment_geometry()
{
    const auto polygons = vector_reader_.get_polygons("lane_groups_polygons");
    const auto& polygon = polygons.front();

    GraphicsGeometry graphics_geometry;

    const auto num_points = polygon.rings.front().size();

    graphics_geometry.vertex_positions.reserve(num_points);
    graphics_geometry.vertex_normals.reserve(num_points);
    graphics_geometry.vertex_colors.reserve(num_points);

    for (const auto& point : polygon.rings.front()) {
        graphics_geometry.vertex_positions.emplace_back(point[0], point[1], 0.0f);
        graphics_geometry.vertex_normals.emplace_back(0.0f, 0.0f, 1.0f);       // toward Z
        graphics_geometry.vertex_colors.emplace_back(0.5f, 0.5f, 0.5f, 1.0f);  // gray, no transparency
    }
    graphics_geometry.indices = mapbox::earcut(polygon.rings);

    return graphics_geometry;
}

}  // namespace Ps::Graphics

// int main()
// {
//     std::vector<Ps::Graphics::Point3f> vertices;
//     std::vector<uint32_t> indices;

//     for (const auto& polygon : polygons) {
//         for (const auto& point : polygon.rings.front()) {
//             vertices.emplace_back(point[0], point[1], 0.0f);
//             // SPDLOG_WARN("({}, {}, {})", point[0], point[1], 0.0f);
//         }
//         indices = mapbox::earcut(polygon.rings);
//         // for (const auto idx : indices) {
//         //     SPDLOG_WARN("{}", idx);
//         // }
//     }

//     Ps::Graphics::GpkgRasterReader raster_reader{map_info};
//     const auto center_tile_id =
//         raster_reader.get_center_tile_id(Ps::Graphics::Point2d{354814.28230467555, 149694.85894189146});
//     SPDLOG_WARN("Center tile: ({}, {})", center_tile_id[0], center_tile_id[1]);
//     const auto tile_ids = raster_reader.get_tile_ids(center_tile_id, 6);
//     for (const auto& tile_id : tile_ids) {
//         // SPDLOG_WARN("({}, {})", tile_id.first, tile_id.second);
//         const auto tile = raster_reader.get_tile(Ps::Graphics::Point2i{tile_id.first, tile_id.second});
//         // SPDLOG_WARN("tile.tile_meter: {}", tile.tile_meter);
//         // SPDLOG_WARN("tile.tile_pixel: {}", tile.tile_pixel);
//         // SPDLOG_WARN("tile.translation: ({}, {})", tile.translation[0], tile.translation[1]);
//         // SPDLOG_WARN("tile.buffer.size(): {}", tile.buffer.size());
//         // SPDLOG_WARN("");
//     }

//     // GDALDataset* dataset = static_cast<GDALDataset*>(
//     //     GDALOpen("/home/saravanan.poosanthiram/Downloads/gh/gh.geotiff", GDALAccess::GA_ReadOnly));
//     // const auto width = GDALGetRasterXSize(dataset);
//     // const auto height = GDALGetRasterYSize(dataset);
//     // SPDLOG_INFO("Raster Size, width: {}, height: {}", width, height);

//     // const auto proj_ref = std:: string{dataset->GetProjectionRef()};
//     // SPDLOG_INFO("Projection Ref: {}", proj_ref);

//     return 0;
// }
