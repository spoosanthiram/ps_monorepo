#include "algo/graph/KargerMinCutGraph.h"

#include <format>
#include <iostream>

namespace Ps::Algo {

KargerMinCutGraph::KargerMinCutGraph(const KargerMinCutGraph& other)
    : Graph<KargerMinCutGraphVertex, Edge<KargerMinCutGraphVertex>>{}
{
    vertices_.reserve(other.vertices_.size());
    for (auto other_vertex : other.vertices_) {
        add_vertex(other_vertex->id());
    }

    edges_.reserve(other.edges_.size());
    for (const auto other_edge : other.edges_) {
        auto u = get_vertex(other_edge->u()->id());
        auto v = get_vertex(other_edge->v()->id());
        edges_.push_back(new Edge<KargerMinCutGraphVertex>{other_edge->id(), u, v});
    }

    for (auto other_vertex : other.vertices_) {
        auto vertex = get_vertex(other_vertex->id());
        for (auto other_edge : other_vertex->edges()) {
            vertex->add_edge(get_edge(other_edge->id()));
        }
    }
}

KargerMinCutGraph::~KargerMinCutGraph()
{
    for (auto edge : edges_) {
        delete edge;
    }

    for (auto vertex : vertices_) {
        delete vertex;
    }
}

uint64_t KargerMinCutGraph::min_cut()
{
    KargerMinCutGraph g = *this;
    uint64_t mincut = vertices_.size();

    uint64_t max_iter = vertices_.size() * vertices_.size();
    for (uint64_t iter = 0; iter < max_iter; ++iter) {
        uint64_t ncut = contract();
        if (ncut < mincut) {
            mincut = ncut;
        }

        std::cerr << std::format("MinCut: {} in iteration: {} of {}", mincut, iter, max_iter) << "\n";

        reset_with(g);
    }

    return mincut;
}

uint64_t KargerMinCutGraph::contract()
{
    num_edges_ = edges_size();

    auto nvertices = vertices_.size();
    while (nvertices > 2) {
        auto e = random_edge();

        auto u = get_vertex(e->u()->id());
        auto v = get_vertex(e->v()->id());

        auto new_vertex = new KargerMinCutGraphVertex{static_cast<vertexid_t>(vertices_.size())};

        adjust_edges(u, v, new_vertex);
        adjust_edges(v, u, new_vertex);

        for (edgeid_t i = 0; i < num_edges_; ++i) {
            auto edge = get_edge(i);
            if (edge->u() == u || edge->u() == v) {
                edge->set_u(new_vertex);
            }
            else if (edge->v() == u || edge->v() == v) {
                edge->set_v(new_vertex);
            }
        }

        vertices_.push_back(new_vertex);

        --nvertices;
    }

    auto edge = random_edge();
    return edge->u()->edges().size();
}

Edge<KargerMinCutGraphVertex>* KargerMinCutGraph::random_edge()
{
    std::uniform_int_distribution<size_t> ud{0, num_edges_ - 1};
    edgeid_t i = ud(random_engine_);
    return edges_[i];
}

void KargerMinCutGraph::remove_edge_at(edgeid_t i)
{
    std::swap(edges_[i], edges_[num_edges_ - 1]);
    edges_[i]->set_id(i);
    edges_[num_edges_ - 1]->set_id(num_edges_ - 1);
    --num_edges_;
}

void KargerMinCutGraph::adjust_edges(const KargerMinCutGraphVertex* u,
                                     const KargerMinCutGraphVertex* v,
                                     KargerMinCutGraphVertex* new_vertex)
{
    for (auto edge : u->edges()) {
        if (edge->v() == v) {
            remove_edge_at(edge->id());
        }
        else {
            edge->set_u(new_vertex);
            new_vertex->add_edge(edge);
            for (auto v_edge : edge->v()->edges()) {
                if (v_edge->v() == u) {
                    v_edge->set_v(new_vertex);
                }
            }
        }
    }
}

void KargerMinCutGraph::reset_with(const KargerMinCutGraph& other)
{
    for (auto other_edge : other.edges_) {
        auto edge = get_edge(other_edge->id());
        edge->set_id(other_edge->id());

        auto u = get_vertex(other_edge->u()->id());
        auto v = get_vertex(other_edge->v()->id());
        edge->set_u(u);
        edge->set_v(v);
    }

    for (auto extra_vertices = vertices_.size() - other.vertices_.size(); extra_vertices > 0; --extra_vertices) {
        delete vertices_.back();
        vertices_.pop_back();
    }

    for (auto other_vertex : other.vertices_) {
        auto vertex = get_vertex(other_vertex->id());

        vertex->clear_edges();
        for (auto other_vertex_edge : other_vertex->edges()) {
            vertex->add_edge(get_edge(other_vertex_edge->id()));
        }
    }
}

} // namespace Ps::Algo
