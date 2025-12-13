#include "algo/graph/StronglyConnectedGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("StronglyConnectedGraph Kosaraju")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/StronglyConnectedAdjList.txt");

    Ps::Algo::StronglyConnectedGraph graph;
    graph.read_adjacency_list(stream);
    CHECK(graph.type() == Ps::Algo::StronglyConnectedGraph::Type::Directed);

    const auto leader_map = graph.kosaraju();
    std::vector<uint32_t> scc;
    for (auto leader_it : leader_map) {
        scc.push_back(leader_it.second);
    }
    std::sort(scc.begin(), scc.end(), std::greater<uint32_t>{});

    std::vector<uint32_t> expected{4, 3, 3, 1};
    CHECK(scc == expected);
}
