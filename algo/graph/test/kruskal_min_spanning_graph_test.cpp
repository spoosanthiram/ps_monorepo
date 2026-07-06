#include "algo/graph/kruskal_min_spanning_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KruskalMinSpanningGraph Mst")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/min_spanning_graph_adj_list.txt");

    ps::algo::KruskalMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    const auto cost = graph.find_mst();
    REQUIRE(cost == 39);
}

TEST_CASE("KruskalMinSpanningGraph AlgoClassMst")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/min_spanning_graph_big_adj_list.txt");

    ps::algo::KruskalMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    const auto cost = graph.find_mst();
    REQUIRE(cost == -3612829);
}

TEST_CASE("KruskalMinSpanningGraph AlgoClassClustering1")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/clustering1.txt");

    ps::algo::KruskalMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    const auto spacing = graph.cluster(4);
    REQUIRE(spacing == 106);
}
