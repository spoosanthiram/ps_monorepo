#include "graphics/avmap/GpkgVectorReader.h"

#include <catch2/catch.hpp>

TEST_CASE("GpkgVectorReader ReadPolygons")
{
    Ps::Graphics::GpkgMapList map_list;
    const auto& map_info = map_list.get_map_info("sg-cetran");
    REQUIRE(map_info != nullptr);

    Ps::Graphics::GpkgVectorReader vector_reader{map_info};
    CHECK(vector_reader.map_cli_major_version() == 11);

    const auto polygons = vector_reader.get_polygons("lane_groups_polygons");
    REQUIRE_FALSE(polygons.empty());

    // first polygon
    {
        const auto& ring0 = polygons[0].rings.front();
        REQUIRE_FALSE(ring0.empty());
    
        const auto& p0 = ring0[0]; // first point is zero
        CHECK(p0[0] == 0.0);
        CHECK(p0[1] == 0.0);

        const auto& p1 = ring0[1];
        CHECK(p1[0] == -7.415154f);
        CHECK(p1[1] == 5.0378447f);

        const auto& p3 = ring0[3];
        CHECK(p3[0] == -3.0530236f);
        CHECK(p3[1] == 11.466338f);
    }

    // 4th polygon
    {
        const auto& ring0 = polygons[4].rings.front();
        REQUIRE_FALSE(ring0.empty());
    
        const auto& p1 = ring0[1];
        CHECK(p1[0] == 0.12139292f);
        CHECK(p1[1] == 0.26860234f);

        const auto& p4 = ring0[4];
        CHECK(p4[0] == -0.75001484f);
        CHECK(p4[1] == 6.4926696f);

        const auto& p6 = ring0[6];
        CHECK(p6[0] == -3.565399f);
        CHECK(p6[1] == 2.335696f);
    }
}
