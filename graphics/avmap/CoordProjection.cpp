#include "CoordProjection.h"

namespace Ps::Graphics {

constexpr auto kDefault_Latlon_Proj = "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs";

CoordProjection::CoordProjection(int32_t epsg)
    : epsg_{epsg}
{
    const auto& epsg_data = EpsgData::get_instance();
    proj_info_ = epsg_data.get_proj_info(epsg_);
    utm_to_latlon_transformer_ =
        proj_create_crs_to_crs(PJ_DEFAULT_CTX, proj_info_.proj4_text.c_str(), kDefault_Latlon_Proj, nullptr);
}

CoordProjection::~CoordProjection()
{
    proj_destroy(utm_to_latlon_transformer_);
}

Point2d CoordProjection::get_xy_from_latlon(const GeoLocation& loc)
{
    PJ_COORD input;
    input.lp.phi = loc.lat().value();
    input.lp.lam = loc.lon().value();
    auto output = proj_trans(utm_to_latlon_transformer_, PJ_INV, input);
    return Point2d{output.xy.x, output.xy.y};
}

}  // namespace Ps::Graphics
