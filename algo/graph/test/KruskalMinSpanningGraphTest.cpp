#include "algo/graph/KruskalMinSpanningGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KruskalMinSpanningGraph Mst")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/MinSpanningGraphAdjList.txt");

    Ps::Algo::KruskalMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    const auto cost = graph.find_mst();
    REQUIRE(cost == 39);
}
