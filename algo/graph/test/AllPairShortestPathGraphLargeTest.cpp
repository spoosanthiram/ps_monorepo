#include "algo/graph/AllPairShortestPathGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass Floyd Warshall Large")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassAPSPLarge.txt");
    Ps::Algo::AllPairShortestPathGraph graph;
    graph.read_adjacency_list(stream);

    std::vector<int> path_cost_matrix;
    bool is_valid = graph.do_floyd_warshall(path_cost_matrix);
    REQUIRE(is_valid);

    for (int i = 0; i < 10; ++i) {
        std::cout << path_cost_matrix[i] << '\n';
    }
}
