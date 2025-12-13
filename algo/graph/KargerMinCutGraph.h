#pragma once

#include "algo/graph/Graph.h"
#include "core/utils/ClassHelper.h"

#include <random>

namespace Ps::Algo {

class KargerMinCutGraphVertex : public Vertex
{
public:
    KargerMinCutGraphVertex(vertexid_t id)
        : Vertex{id}
    {}
    ~KargerMinCutGraphVertex() override = default;

    const std::vector<Edge<KargerMinCutGraphVertex>*>& edges() const { return edges_; }

    void add_edge(Edge<KargerMinCutGraphVertex>* e) { edges_.push_back(e); }
    void clear_edges() { edges_.clear(); }

private:
    std::vector<Edge<KargerMinCutGraphVertex>*> edges_;
};

class KargerMinCutGraph : public Graph<KargerMinCutGraphVertex, Edge<KargerMinCutGraphVertex>>
{
public:
    KargerMinCutGraph() = default;
    KargerMinCutGraph(const KargerMinCutGraph& other);
    MOVE_CONSTRUCTOR(KargerMinCutGraph) = delete;
    ~KargerMinCutGraph() override;

    COPY_ASSIGNMENT(KargerMinCutGraph) = delete;
    MOVE_ASSIGNMENT(KargerMinCutGraph) = delete;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    KargerMinCutGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id]; }
    Edge<KargerMinCutGraphVertex>* get_edge(edgeid_t id) const override { return edges_[id]; }

    void add_vertex(vertexid_t id) override
    {
        auto v = new KargerMinCutGraphVertex{id};
        vertices_.push_back(v);
    }
    edgeid_t add_edge(edgeid_t id, KargerMinCutGraphVertex* u, KargerMinCutGraphVertex* v, int32_t /*value*/) override
    {
        auto e = new Edge<KargerMinCutGraphVertex>{id, u, v};
        u->add_edge(e);
        edges_.push_back(e);
        ++id;

        if (type() == Type::Undirected) {
            e = new Edge<KargerMinCutGraphVertex>{id, v, u};
            v->add_edge(e);
            edges_.push_back(e);
            ++id;
        }

        return id;
    }

    uint64_t min_cut();

private:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

    uint64_t contract();
    Edge<KargerMinCutGraphVertex>* random_edge();
    void remove_edge_at(edgeid_t i);
    void adjust_edges(const KargerMinCutGraphVertex* u,
                      const KargerMinCutGraphVertex* v,
                      KargerMinCutGraphVertex* new_vertex);
    void reset_with(const KargerMinCutGraph& other);

private:
    std::vector<KargerMinCutGraphVertex*> vertices_;
    std::vector<Edge<KargerMinCutGraphVertex>*> edges_;

    edgeid_t num_edges_{0};
    std::default_random_engine random_engine_;
};

} // namespace Ps::Algo
