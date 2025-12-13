#include "algo/graph/StronglyConnectedGraph.h"

namespace Ps::Algo {

edgeid_t StronglyConnectedGraph::add_edge(edgeid_t id,
                                          StronglyConnectedGraphVertex* u,
                                          StronglyConnectedGraphVertex* v,
                                          int32_t /*value*/)
{
    edges_.push_back(std::make_unique<Edge<StronglyConnectedGraphVertex>>(id, u, v));
    auto edge = edges_.back().get();
    edge->u()->add_edge(edge);

    reverse_edges_.push_back(std::make_unique<Edge<StronglyConnectedGraphVertex>>(edge->id(), edge->v(), edge->u()));
    auto reverse_edge = reverse_edges_.back().get();
    edge->v()->add_reverse_edge(reverse_edge);

    ++id;

    return id;
}

std::unordered_map<vertexid_t, uint32_t> StronglyConnectedGraph::kosaraju()
{
    finish_time_ = 0; // make sure finish_time_ = 0 before starting

    dfs_loop_reverse();

    vertices_by_finish_time_.resize(vertices_.size()); // resize, so we can index

    for (auto& v : vertices_) {
        v->set_explored(false);
        vertices_by_finish_time_[v->finish_time()] = v.get();
    }

    dfs_loop();

    std::unordered_map<vertexid_t, uint32_t> leader_map;
    for (auto& v : vertices_) {
        ++leader_map[v->leader()->id()];
    }

    return leader_map;
}

void StronglyConnectedGraph::dfs_loop_reverse()
{
    for (auto rit = vertices_.rbegin(); rit != vertices_.rend(); ++rit) {
        if (!(*rit)->explored()) {
            dfs_reverse(rit->get());
        }
    }
}

void StronglyConnectedGraph::dfs_reverse(StronglyConnectedGraphVertex* v)
{
    v->set_explored(true);
    for (auto e : v->reverse_edges()) {
        if (!e->v()->explored()) {
            dfs_reverse(e->v());
        }
    }
    v->set_finish_time(next_finish_time());
}

void StronglyConnectedGraph::dfs_loop()
{
    StronglyConnectedGraphVertex* v;
    for (auto rit = vertices_by_finish_time_.rbegin(); rit != vertices_by_finish_time_.rend(); ++rit) {
        v = *rit;
        if (!v->explored()) {
            dfs(v, v);
        }
    }
}

void StronglyConnectedGraph::dfs(StronglyConnectedGraphVertex* v, StronglyConnectedGraphVertex* leader)
{
    v->set_explored(true);
    v->set_leader(leader);
    for (auto e : v->edges()) {
        if (!e->v()->explored()) {
            dfs(e->v(), leader);
        }
    }
}

} // namespace Ps::Algo
