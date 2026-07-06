#include "algo/graph/strongly_connected_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("StronglyConnectedGraph Kosaraju")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/strongly_connected_adj_list.txt");

    ps::algo::StronglyConnectedGraph graph;
    graph.read_adjacency_list(stream);
    CHECK(graph.type() == ps::algo::StronglyConnectedGraph::Type::Directed);

    const auto leader_map = graph.kosaraju();
    std::vector<uint32_t> scc;
    for (auto leader_it : leader_map) {
        scc.push_back(leader_it.second);
    }
    std::sort(scc.begin(), scc.end(), std::greater<uint32_t>{});

    std::vector<uint32_t> expected{4, 3, 3, 1};
    CHECK(scc == expected);
}
