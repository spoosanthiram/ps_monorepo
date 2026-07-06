#include "algo/graph/all_pair_shortest_path_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass Floyd Warshall 1")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/all_pair_shortest_pair1.txt");
    ps::algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE_FALSE(is_valid);
}

TEST_CASE("AlgoClass Floyd Warshall 2")
{
    ps::algo::AllPairShortestPathGraph graph;
    auto stream = ps::utils::open_stream("algo/graph/test/data/all_pair_shortest_pair2.txt");
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE_FALSE(is_valid);
}

TEST_CASE("AlgoClass Floyd Warshall 3")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/all_pair_shortest_pair3.txt");
    ps::algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE(is_valid);
    auto it = std::min_element(path_cost_matrix.begin(), path_cost_matrix.end());
    REQUIRE(*it == -19);
}
