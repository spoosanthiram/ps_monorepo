#include "algo/graph/prim_min_spanning_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("PrimMinSpanningGraph Mst")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/min_spanning_graph_adj_list.txt");

    ps::algo::PrimMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    long cost = graph.find_mst();
    REQUIRE(cost == 39);
}

TEST_CASE("PrimMinSpanningGraph AlgoClassMst")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/min_spanning_graph_big_adj_list.txt");

    ps::algo::PrimMinSpanningGraph graph;
    graph.read_adjacency_list(stream);

    long cost = graph.find_mst();
    REQUIRE(cost == -3612829);
}
