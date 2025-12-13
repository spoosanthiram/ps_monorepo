#include "graphics/geometry/ModelReader.h"

#include <catch2/catch.hpp>

TEST_CASE("ModelReader ReadObj")
{
    auto geometry = Ps::Graphics::read_model("graphics/data/models/cube.obj");
    CHECK(geometry.vertex_positions.size() == 8);
}
