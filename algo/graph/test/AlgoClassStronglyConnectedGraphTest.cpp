#include "algo/graph/StronglyConnectedGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("StronglyConnectedGraph AlgoClassKosaraju")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassStronglyConnectedAdjList.txt");

    Ps::Algo::StronglyConnectedGraph graph;
    graph.read_adjacency_list(stream);
    CHECK(graph.type() == Ps::Algo::StronglyConnectedGraph::Type::Directed);

    std::vector<unsigned int> expected{434821, 968, 459, 313, 211};

    const auto leader_map = graph.kosaraju();
    REQUIRE(leader_map.size() >= expected.size());

    std::vector<unsigned int> scc;
    for (auto leader_it : leader_map) {
        scc.push_back(leader_it.second);
    }

    std::sort(scc.begin(), scc.end(), std::greater<unsigned int>{});

    std::vector<unsigned int> scc2{scc.begin(), scc.begin() + expected.size()};
    CHECK(scc2 == expected);
}
