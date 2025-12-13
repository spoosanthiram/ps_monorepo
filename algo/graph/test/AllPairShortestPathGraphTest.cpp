#include "algo/graph/AllPairShortestPathGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass Floyd Warshall 1")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassAPSP1.txt");
    Ps::Algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE_FALSE(is_valid);
}

TEST_CASE("AlgoClass Floyd Warshall 2")
{
    Ps::Algo::AllPairShortestPathGraph graph;
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassAPSP2.txt");
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE_FALSE(is_valid);
}

TEST_CASE("AlgoClass Floyd Warshall 3")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassAPSP3.txt");
    Ps::Algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);

    REQUIRE(is_valid);
    auto it = std::min_element(path_cost_matrix.begin(), path_cost_matrix.end());
    REQUIRE(*it == -19);
}
