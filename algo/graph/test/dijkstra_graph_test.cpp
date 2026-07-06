#include "algo/graph/dijkstra_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

#include <array>

TEST_CASE("DijkstraGraph ShortestPath")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/dijkstra_adj_list.txt");

    ps::algo::DijkstraGraph graph;
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

TEST_CASE("DijkstraGraph AlgoClassShortestPath")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/dijkstra_big_adj_list.txt");

    ps::algo::DijkstraGraph graph;
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
