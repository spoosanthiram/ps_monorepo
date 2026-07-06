#include "algo/graph/bellman_ford_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("BellmanFord ShortestPath")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/bellman_ford_adj_list.txt");
    ps::algo::BellmanFordGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_costs;
    const auto costs_valid = graph.find_shortest_path(0, path_costs);
    REQUIRE(costs_valid);
    std::vector<int> expected_costs{0, 2, 3, 4, 6};
    REQUIRE(expected_costs == path_costs);
}

TEST_CASE("BellmanFord ShortestPath2")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/bellman_ford_adj_list2.txt");
    ps::algo::BellmanFordGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_costs;
    const auto costs_vaild = graph.find_shortest_path(0, path_costs);

    REQUIRE_FALSE(costs_vaild); // Graph have negative cycle
}
