#include "algo/other/traveling_salesman.h"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("TravelingSalesman Simple Tour")
{
    ps::algo::TravelingSalesman tsp;
    tsp.read("algo/other/test/data/tsp.txt");
    auto distance = tsp.tour();
    CHECK(distance == Catch::Approx{7.88635});
}
