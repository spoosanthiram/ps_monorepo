#include "algo/graph/KargerMinCutGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KargerMinCutGraph AlgoClassMinCut")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassKargerMinCutAdjList.txt");

    Ps::Algo::KargerMinCutGraph graph;
    graph.read_adjacency_list(stream);

    const auto cuts = graph.min_cut();
    REQUIRE(cuts == 17);
}
