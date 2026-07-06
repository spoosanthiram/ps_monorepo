#include "algo/graph/all_pair_shortest_path_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass Floyd Warshall Large")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/all_pair_shortest_pair_large.txt");
    ps::algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);
    REQUIRE(is_valid);

    for (int i = 0; i < 10; ++i) {
        std::cout << path_cost_matrix[i] << '\n';
    }
}
