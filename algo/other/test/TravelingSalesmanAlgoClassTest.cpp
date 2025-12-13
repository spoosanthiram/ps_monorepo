#include "algo/other/TravelingSalesman.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("TravelingSalesman AlgoClass Tour")
{
    Ps::Algo::TravelingSalesman tsp;
    tsp.read("algo/other/test/data/AlgoClassTsp.txt");
    auto distance = tsp.tour();
    CHECK(static_cast<int>(distance) == 26442);
}
