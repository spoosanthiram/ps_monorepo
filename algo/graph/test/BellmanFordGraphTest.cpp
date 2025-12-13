#include "algo/graph/BellmanFordGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("BellmanFord ShortestPath")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/BellmanFordAdjList.txt");
    Ps::Algo::BellmanFordGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_costs;
    const auto costs_valid = graph.find_shortest_path(0, path_costs);
    REQUIRE(costs_valid);
    std::vector<int> expected_costs{0, 2, 3, 4, 6};
    REQUIRE(expected_costs == path_costs);
}

TEST_CASE("BellmanFord ShortestPath2")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/BellmanFordAdjList2.txt");
    Ps::Algo::BellmanFordGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_costs;
    const auto costs_vaild = graph.find_shortest_path(0, path_costs);

    REQUIRE_FALSE(costs_vaild); // Graph have negative cycle
}
