#include "algo/graph/PrimMinSpanningGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("PrimMinSpanningGraph Mst")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/MinSpanningGraphAdjList.txt");

    Ps::Algo::PrimMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    long cost = graph.find_mst();
    REQUIRE(cost == 39);
}
