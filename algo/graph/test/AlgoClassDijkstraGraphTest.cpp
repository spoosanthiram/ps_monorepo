#include "algo/graph/DijkstraGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <array>

TEST_CASE("DijkstraGraph AlgoClassShortestPath")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassDijkstraAdjList.txt");

    Ps::Algo::DijkstraGraph graph;
    graph.read_adjacency_list(stream);

    graph.find_shortest_path(0);

    std::array<int, 10> expected{2599, 2610, 2947, 2052, 2367, 2399, 2029, 2442, 2505, 3068};

    std::array<int, 10> vertices{6, 36, 58, 81, 98, 114, 132, 164, 187, 196};
    std::array<int, 10> actual;
    for (size_t i = 0; i < actual.size(); ++i) {
        actual[i] = graph.get_vertex(vertices[i])->distance();
    }
    REQUIRE(actual == expected);
}
