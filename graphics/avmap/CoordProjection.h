#pragma once

#include "EpsgData.h"

#include "graphics/geometry/GraphicsGeometry.h"

#include <proj.h>

namespace Ps::Graphics {

class CoordProjection
{
public:
    CoordProjection(int32_t epsg);
    ~CoordProjection();

    Point2d get_xy_from_latlon(const GeoLocation& loc);

private:
    int32_t epsg_{0};
    EpsgData::ProjectionInfo proj_info_;
    PJ* utm_to_latlon_transformer_{nullptr};
};

}  // namespace Ps::Graphics
