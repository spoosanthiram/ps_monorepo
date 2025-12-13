#include "algo/graph/BellmanFordGraph.h"

#include <limits>

namespace Ps::Algo {

BellmanFordGraph::~BellmanFordGraph()
{
    for (auto edge : edges_) {
        delete edge;
    }

    for (auto vertex : vertices_) {
        delete vertex;
    }
}

bool BellmanFordGraph::find_shortest_path(vertexid_t source_vertex_id, std::vector<int>& cost)
{
    std::vector<int> prev_cost;

    cost.reserve(vertices_.size());
    prev_cost.reserve(vertices_.size());

    for (size_t i = 0; i < vertices_.size(); ++i) {
        cost.push_back(std::numeric_limits<int>::max());
        prev_cost.push_back(std::numeric_limits<int>::max());
    }

    prev_cost[source_vertex_id] = 0;

    auto cost_changed = false;

    for (size_t i = 1; i < vertices_.size(); ++i) {
        cost_changed = inner_iteration(cost, prev_cost);
        if (!cost_changed) {
            break;
        }
    }

    if (cost_changed) {
        cost_changed = inner_iteration(cost, prev_cost);
    }

    return !cost_changed;
}

bool BellmanFordGraph::inner_iteration(std::vector<int>& cost, std::vector<int>& prev_cost)
{
    auto cost_changed = false;

    for (auto v : vertices_) {
        auto min_cost = std::numeric_limits<int>::max();
        for (auto e : v->in_edges()) {
            if (prev_cost[e->u()->id()] != std::numeric_limits<int>::max()) {
                min_cost = std::min(min_cost, prev_cost[e->u()->id()] + e->cost());
            }
        }
        if (min_cost < prev_cost[v->id()]) {
            cost[v->id()] = min_cost;
            cost_changed = true;
            prev_cost[v->id()] = cost[v->id()];
        }
        else {
            cost[v->id()] = prev_cost[v->id()];
        }
    }

    return cost_changed;
}

} // namespace Ps::Algo
