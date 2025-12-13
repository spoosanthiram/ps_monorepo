#include "algo/graph/KargerMinCutGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KargerMinCutGraph MinCut")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/KargerMinCutAdjList.txt");

    Ps::Algo::KargerMinCutGraph graph;
    graph.read_adjacency_list(stream);

    REQUIRE(graph.vertices_size() == 4);
    REQUIRE(graph.edges_size() == 10);

    const auto cuts = graph.min_cut();
    REQUIRE(cuts == 2);
}
