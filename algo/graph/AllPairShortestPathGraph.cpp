#include "algo/graph/AllPairShortestPathGraph.h"

#include <limits>

namespace Ps::Algo {

AllPairShortestPathGraph::~AllPairShortestPathGraph()
{
    for (auto edge : edges_) {
        delete edge;
    }

    for (auto vertex : vertices_) {
        delete vertex;
    }
}

bool AllPairShortestPathGraph::do_floyd_warshall(std::vector<int>& path_cost_matrix)
{
    const auto num_vertices = static_cast<unsigned int>(vertices_size());

    path_cost_matrix.reserve(num_vertices * num_vertices);

    std::vector<int> prev_path_cost_matrix;
    prev_path_cost_matrix.reserve(num_vertices * num_vertices);

    path_cost_matrix.assign(num_vertices * num_vertices, std::numeric_limits<int>::max());
    prev_path_cost_matrix.assign(num_vertices * num_vertices, std::numeric_limits<int>::max());

    for (unsigned int i = 0; i < num_vertices; ++i) {
        prev_path_cost_matrix[i * num_vertices + i] = 0;
    }

    for (auto e : edges_) {
        prev_path_cost_matrix[e->u()->id() * num_vertices + e->v()->id()] = e->get_cost();
    }

    for (auto k = 0u; k < num_vertices; ++k) {
        for (auto i = 0u; i < num_vertices; ++i) {
            for (auto j = 0u; j < num_vertices; ++j) {
                const auto cost1 = prev_path_cost_matrix[i * num_vertices + k];
                const auto cost2 = prev_path_cost_matrix[k * num_vertices + j];
                const auto new_cost = cost1 + cost2;
                const auto index = i * num_vertices + j;
                if (cost1 != std::numeric_limits<int>::max() && cost2 != std::numeric_limits<int>::max() &&
                    new_cost < prev_path_cost_matrix[index]) {
                    path_cost_matrix[index] = new_cost;
                }
                else {
                    path_cost_matrix[index] = prev_path_cost_matrix[index];
                }
            }
        }
        std::copy(path_cost_matrix.begin(), path_cost_matrix.end(), prev_path_cost_matrix.begin());
    }

    auto has_negative_cycle = false;
    for (auto i = 0u; i < num_vertices; ++i) {
        if (prev_path_cost_matrix[i * num_vertices + i] < 0) {
            has_negative_cycle = true;
            break;
        }
    }

    return !has_negative_cycle;
}

} // namespace Ps::Algo
