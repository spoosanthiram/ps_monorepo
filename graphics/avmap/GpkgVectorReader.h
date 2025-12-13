#pragma once

#include "CoordProjection.h"
#include "GpkgMapList.h"

#include "graphics/geometry/GraphicsGeometry.h"

class OGRFeature;
class OGRPoint;

namespace Ps::Graphics {

class GpkgVectorReader
{
public:
    struct Polygon
    {
        OGRFeature* ogr_feature{nullptr};
        Point2d translation;
        std::vector<std::vector<std::array<float, 2>>> rings;
    };

public:
    GpkgVectorReader(const std::shared_ptr<GpkgMapList::MapInfo>& map_info);

    int32_t map_cli_major_version() const { return map_cli_major_version_; }
    std::vector<Polygon> get_polygons(const std::string& layer_name);

private:
    Polygon get_polygon(OGRFeature* feature);
    Point2d to_local_point(const OGRPoint& pos);

private:
    std::shared_ptr<GpkgMapList::MapInfo> map_info_;
    CoordProjection proj_;
    int32_t map_cli_major_version_{0};
};

}  // namespace Ps::Graphics
