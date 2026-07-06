#include "algo/graph/karger_mincut_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("KargerMinCutGraph AlgoClassMinCut")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/karger_mincut_big_adj_list.txt");

    ps::algo::KargerMinCutGraph graph;
    graph.read_adjacency_list(stream);

    const auto cuts = graph.min_cut();
    REQUIRE(cuts == 17);
}
