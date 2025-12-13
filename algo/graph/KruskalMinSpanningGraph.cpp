#include "KruskalMinSpanningGraph.h"

#include <forward_list>

namespace Ps::Algo {

bool less_than(const std::unique_ptr<KruskalMinSpanningGraphEdge>& x,
               const std::unique_ptr<KruskalMinSpanningGraphEdge>& y)
{
    return x->cost() < y->cost();
}

long KruskalMinSpanningGraph::find_mst()
{
    long cost = 0;

    std::sort(edges_.begin(), edges_.end(), less_than);

    for (auto& e : edges_) {
        auto u_cluster = find_leader(e->u());
        auto v_cluster = find_leader(e->v());
        if (u_cluster != v_cluster) {
            cost += e->cost();
            union_leaders(u_cluster, v_cluster);
        }
    }

    return cost;
}

unsigned int KruskalMinSpanningGraph::cluster(unsigned int k_cluster)
{
    std::sort(edges_.begin(), edges_.end(), less_than);

    std::size_t n_cluster = vertices_.size();
    if (n_cluster <= k_cluster) {
        return static_cast<unsigned int>(n_cluster);
    }

    auto it = edges_.begin();
    for (; it != edges_.end(); ++it) {
        auto& edge = *it;
        auto u_cluster = find_leader(edge->u());
        auto v_cluster = find_leader(edge->v());
        if (u_cluster != v_cluster) {
            union_leaders(u_cluster, v_cluster);
            --n_cluster;
            if (n_cluster == k_cluster) {
                break;
            }
        }
    }

    unsigned int spacing = 0;

    for (; it != edges_.end(); ++it) {
        auto& edge = *it;
        auto u_cluster = find_leader(edge->u());
        auto v_cluster = find_leader(edge->v());
        if (u_cluster != v_cluster) { // first edge that is not in a cluster is the spacing as edges are sorted.
            spacing = edge->cost();
            break;
        }
    }

    return spacing;
}

KruskalMinSpanningGraphVertex* KruskalMinSpanningGraph::find_leader(KruskalMinSpanningGraphVertex* v)
{
    if (v->leader() == v || v->leader()->leader() == v->leader()) {
        return v->leader();
    }

    std::forward_list<KruskalMinSpanningGraphVertex*> vertices;
    while (v->leader() != v) {
        vertices.push_front(v);
        v = v->leader();
    }

    vertices.pop_front();
    for (auto u : vertices) {
        u->set_leader(v);
    }

    return v;
}

void KruskalMinSpanningGraph::union_leaders(KruskalMinSpanningGraphVertex* u, KruskalMinSpanningGraphVertex* v)
{
    if (u->rank() > v->rank()) {
        v->set_leader(u);
    }
    else if (u->rank() < v->rank()) {
        u->set_leader(v);
    }
    else {
        u->set_rank(u->rank() + 1);
        v->set_leader(u);
    }
}

} // namespace Ps::Algo
