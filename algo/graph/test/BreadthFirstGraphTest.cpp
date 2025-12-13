#include "algo/graph/BreadthFirstGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("BreadthFirstGraph Search")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/BreadthFirstAdjList.txt");
    Ps::Algo::BreadthFirstGraph graph;
    graph.read_adjacency_list(stream);

    REQUIRE(graph.vertices_size() == 5);
    REQUIRE(graph.edges_size() == 14);

    const auto dist = graph.find_distance(0, 2);
    REQUIRE(dist == 2);
}
