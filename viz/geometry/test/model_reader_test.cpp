#include "viz/geometry/model_reader.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ModelReader ReadObj")
{
    auto geometry = ps::viz::read_model("viz/data/models/cube.obj");
    CHECK(geometry.vertex_positions.size() == 8);
}
