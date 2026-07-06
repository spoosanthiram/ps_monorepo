#include "algo/graph/bit_vertex_clustering_graph.h"
#include "utils/utils.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

TEST_CASE("AlgoClass BitVertexClustering")
{
    auto stream = ps::utils::open_stream("algo/graph/test/data/clustering_big.txt");
    ps::algo::BitVertexClusteringGraph graph;
    graph.read(stream);

    auto t = std::chrono::steady_clock::now();
    graph.build_edges();
    auto d = std::chrono::steady_clock::now() - t;
    std::cout << "build_edges(): " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms"
              << std::endl;

    int ncluster = graph.cluster();
    REQUIRE(ncluster == 6118);
}
