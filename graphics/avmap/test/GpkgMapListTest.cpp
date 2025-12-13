#include "graphics/avmap/GpkgMapList.h"

#include <catch2/catch.hpp>

TEST_CASE("GpkgMapList MapInfo")
{
    Ps::Graphics::GpkgMapList map_list;

    const auto& map_names = map_list.get_map_names();
    REQUIRE(map_names.size() == 3);
    REQUIRE(map_names[0] == "sg-cetran");
    REQUIRE(map_names[1] == "us-nv-las-vegas-strip");
    REQUIRE(map_names[2] == "us-pa-pittsburgh-hazelwood");

    // us-pa-pittsburgh-hazelwood
    {
        const auto& map_info = map_list.get_map_info("us-pa-pittsburgh-hazelwood");
        REQUIRE(map_info != nullptr);

        CHECK(map_info->gpkg_path == "graphics/data/maps/us-pa-pittsburgh-hazelwood/map.gpkg");

        CHECK(map_info->raster_dataset != nullptr);
        CHECK(map_info->top_left == Ps::Graphics::Point2d{583040, 4477312});
        CHECK(map_info->meter_per_pixel == 0.1);
        CHECK(map_info->raster_center == Ps::Graphics::Point2d{586355.2, 4475507.2});
        CHECK(map_info->epsg == 32617);
        CHECK(map_info->no_data_value == 0);

        CHECK(map_info->vector_dataset != nullptr);
        CHECK(map_info->geo_loc.lat().value() == 40.425909531510115);
        CHECK(map_info->geo_loc.lon().value() == -79.98184204101562);
        CHECK(map_info->vector_center == Ps::Graphics::Point2d{586368.0227096782, 4475528.40737085});
    }

    // us-nv-las-vegas-strip
    {
        const auto& map_info = map_list.get_map_info("us-nv-las-vegas-strip");
        REQUIRE(map_info != nullptr);

        CHECK(map_info->gpkg_path == "graphics/data/maps/us-nv-las-vegas-strip/map.gpkg");

        CHECK(map_info->raster_dataset != nullptr);
        CHECK(map_info->top_left == Ps::Graphics::Point2d{663628.8, 4002073.6});
        CHECK(map_info->meter_per_pixel == 0.1);
        CHECK(map_info->raster_center == Ps::Graphics::Point2d{666726.4, 3997196.8});
        CHECK(map_info->epsg == 32611);
        CHECK(map_info->no_data_value == 0);

        CHECK(map_info->vector_dataset != nullptr);
        CHECK(map_info->geo_loc.lat().value() == 36.10520733313917);
        CHECK(map_info->geo_loc.lon().value() == -115.1480484008789);
        CHECK(map_info->vector_center == Ps::Graphics::Point2d{666698.9633236346, 3997205.446330774});
    }

    // sg-cetran
    {
        const auto& map_info = map_list.get_map_info("sg-cetran");
        REQUIRE(map_info != nullptr);

        CHECK(map_info->gpkg_path == "graphics/data/maps/sg-cetran/map.gpkg");

        CHECK(map_info->raster_dataset != nullptr);
        CHECK(map_info->top_left == Ps::Graphics::Point2d{354534.4, 150016});
        CHECK(map_info->meter_per_pixel == 0.1);
        CHECK(map_info->raster_center == Ps::Graphics::Point2d{354854.4, 149593.6});
        CHECK(map_info->epsg == 32648);
        CHECK(map_info->no_data_value == 0);

        CHECK(map_info->vector_dataset != nullptr);
        CHECK(map_info->geo_loc.lat().value() == 1.3547111750290373);
        CHECK(map_info->geo_loc.lon().value() == 103.69548797607422);
        CHECK(map_info->vector_center == Ps::Graphics::Point2d{354868.16496664437, 149775.6348020796});
    }
}
