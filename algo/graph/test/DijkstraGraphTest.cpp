#include "algo/graph/DijkstraGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <array>

TEST_CASE("DijkstraGraph ShortestPath")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/DijkstraAdjList.txt");

    Ps::Algo::DijkstraGraph graph;
    graph.read_adjacency_list(stream);

    graph.find_shortest_path(0);

    std::array<int, 10> expected{0, 10, 6, 7, 5, 13, 9, 16, 20, 19};
    std::array<int, 10> actual;
    for (int i = 0; i < 10; ++i) {
        auto v = graph.get_vertex(i);
        actual[i] = v->distance();
    }
    REQUIRE(actual == expected);
}
