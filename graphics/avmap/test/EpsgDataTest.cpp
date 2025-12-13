#include "graphics/avmap/EpsgData.h"

#include <catch2/catch.hpp>

TEST_CASE("EpsgData ProjectionInfo")
{
    const auto& epsg_data = Ps::Graphics::EpsgData::get_instance();
    const auto& proj_info_map = epsg_data.get_proj_info_map();
    REQUIRE_FALSE(proj_info_map.empty());

    // EPSG 32648
    {
        const auto& proj_info = epsg_data.get_proj_info(32648);
        CHECK(proj_info.name == "# WGS 84 / UTM zone 48N");
        CHECK(proj_info.proj4_text == "+proj=utm +zone=48 +datum=WGS84 +units=m +no_defs  ");
    }

    // EPSG 32617
    {
        const auto& proj_info = epsg_data.get_proj_info(32617);
        CHECK(proj_info.name == "# WGS 84 / UTM zone 17N");
        CHECK(proj_info.proj4_text == "+proj=utm +zone=17 +datum=WGS84 +units=m +no_defs  ");
    }

    // EPSG 32611
    {
        const auto& proj_info = epsg_data.get_proj_info(32611);
        CHECK(proj_info.name == "# WGS 84 / UTM zone 11N");
        CHECK(proj_info.proj4_text == "+proj=utm +zone=11 +datum=WGS84 +units=m +no_defs  ");
    }
}
