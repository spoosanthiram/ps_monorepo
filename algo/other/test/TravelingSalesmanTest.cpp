#include "algo/other/TravelingSalesman.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TravelingSalesman Simple Tour")
{
    Ps::Algo::TravelingSalesman tsp;
    tsp.read("algo/other/test/data/Tsp.txt");
    auto distance = tsp.tour();
    CHECK(distance == Catch::Approx{7.88635});
}
