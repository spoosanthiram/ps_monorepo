#include "graphics/geometry/gltf_reader.h"

#include <catch2/catch.hpp>

TEST_CASE("GlTF Invalid File")
{
    REQUIRE_THROWS(Ps::Graphics::GlTF{"invalid.gltf"});
}

TEST_CASE("GlTF Simple")
{
    Ps::Graphics::GlTF{"graphics/data/models/triangle-embedded.gltf"};
}

TEST_CASE("GlTF Box Embedded")
{
    Ps::Graphics::GlTF{"graphics/data/models/box/gltf-embedded/box.gltf"};
}

TEST_CASE("GlTF Box")
{
    Ps::Graphics::GlTF{"graphics/data/models/box/gltf/box.gltf"};
}
