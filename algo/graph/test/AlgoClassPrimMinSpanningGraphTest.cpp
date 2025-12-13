#include "algo/graph/PrimMinSpanningGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("PrimMinSpanningGraph AlgoClassMst")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassMinSpanningGraphAdjList.txt");

    Ps::Algo::PrimMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    long cost = graph.find_mst();
    REQUIRE(cost == -3612829);
}
