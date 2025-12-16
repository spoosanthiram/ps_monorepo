#pragma once

#include "viz/geometry/viz_defs.h"

namespace Ps::Viz {

class Ray
{
public:
    Ray(const Point3d& origin, const Vector3d& dir)
        : origin_{origin}
        , direction_{dir}
    {}

    const Point3d& origin() const { return origin_; }
    const Vector3d& direction() const { return direction_; }

    Point3d point_at_parameter(float t) const { return origin_ + (t * direction_); }

private:
    Point3d origin_;
    Vector3d direction_;
};

} // namespace Ps::Viz
