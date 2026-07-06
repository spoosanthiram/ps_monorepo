#include "algo/graph/breadth_first_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("BreadthFirstGraph Search")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/breadth_first_adj_list.txt");
    ps::algo::BreadthFirstGraph graph;
    graph.read_adjacency_list(stream);

    REQUIRE(graph.vertices_size() == 5);
    REQUIRE(graph.edges_size() == 14);

    const auto dist = graph.find_distance(0, 2);
    REQUIRE(dist == 2);
}
