#include "algo/graph/BitVertexClusteringGraph.h"
#include "core/utils/Utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass BitVertexClustering")
{
    auto stream = Ps::Core::open_stream("algo/graph/test/data/AlgoClassClusteringBig.txt");
    Ps::Algo::BitVertexClusteringGraph graph;
    graph.read(stream);

    auto t = std::chrono::steady_clock::now();
    graph.build_edges();
    auto d = std::chrono::steady_clock::now() - t;
    std::cout << "build_edges(): " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms"
              << std::endl;

    int ncluster = graph.cluster();
    REQUIRE(ncluster == 6118);
}
