#include "algo/other/traveling_salesman.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("TravelingSalesman AlgoClass Tour")
{
    ps::algo::TravelingSalesman tsp;
    tsp.read("algo/other/test/data/tsp_large.txt");
    auto distance = tsp.tour();
    CHECK(static_cast<int>(distance) == 26442);
}
