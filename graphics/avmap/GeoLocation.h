#pragma once

#include <units.h>

namespace Ps::Graphics {

class GeoLocation
{
public:
    GeoLocation() = default;
    GeoLocation(const units::angle::degree_t& lat, const units::angle::degree_t& lon)
        : latitude_{lat}
        , longitude_{lon}
    {}

    const units::angle::degree_t& lat() const { return latitude_; }
    const units::angle::degree_t& lon() const { return longitude_; }

private:
    units::angle::degree_t latitude_{0.0};
    units::angle::degree_t longitude_{0.0};
};

}  // namespace Ps::Graphics
