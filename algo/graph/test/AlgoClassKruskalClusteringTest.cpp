#include "algo/graph/KruskalMinSpanningGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KruskalMinSpanningGraph AlgoClassClustering1")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassClustering1.txt");

    Ps::Algo::KruskalMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    const auto spacing = graph.cluster(4);
    REQUIRE(spacing == 106);
}
