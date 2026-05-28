#include "viz/geometry/gltf_reader.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("GlTF Invalid File")
{
    REQUIRE_THROWS(ps::viz::GlTF{"invalid.gltf"});
}

TEST_CASE("GlTF Simple")
{
    ps::viz::GlTF{"viz/data/models/triangle-embedded.gltf"};
}

TEST_CASE("GlTF Box Embedded")
{
    ps::viz::GlTF{"viz/data/models/box/gltf-embedded/box.gltf"};
}

// TODO(AL-31): uncomment when the ticket done
// TEST_CASE("GlTF Box")
// {
//     ps::viz::GlTF{"viz/data/models/box/gltf/box.gltf"};
// }
