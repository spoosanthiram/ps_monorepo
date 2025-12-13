#pragma once

#include "algo/graph/Graph.h"
#include "core/utils/ClassHelper.h"

#include <memory>

namespace Ps::Algo {

class KruskalMinSpanningGraphVertex : public Vertex
{
public:
    KruskalMinSpanningGraphVertex(vertexid_t id)
        : Vertex{id}
        , leader_{this}
    {}

    KruskalMinSpanningGraphVertex* leader() const { return leader_; }
    int rank() const { return rank_; }

    void set_leader(KruskalMinSpanningGraphVertex* leader) { leader_ = leader; }
    void set_rank(int rank) { rank_ = rank; }

private:
    KruskalMinSpanningGraphVertex* leader_;
    int rank_{0};
};

class KruskalMinSpanningGraphEdge : public Edge<KruskalMinSpanningGraphVertex>
{
public:
    KruskalMinSpanningGraphEdge(edgeid_t id,
                                KruskalMinSpanningGraphVertex* u,
                                KruskalMinSpanningGraphVertex* v,
                                int cost)
        : Edge<KruskalMinSpanningGraphVertex>{id, u, v}
        , cost_{cost}
    {}

    int cost() const { return cost_; }

private:
    int cost_;
};

class KruskalMinSpanningGraph : public Graph<KruskalMinSpanningGraphVertex, KruskalMinSpanningGraphEdge>
{
public:
    KruskalMinSpanningGraph() = default;
    ~KruskalMinSpanningGraph() = default;

    COPY_CONSTRUCTOR(KruskalMinSpanningGraph) = delete;
    MOVE_CONSTRUCTOR(KruskalMinSpanningGraph) = delete;
    COPY_ASSIGNMENT(KruskalMinSpanningGraph) = delete;
    MOVE_ASSIGNMENT(KruskalMinSpanningGraph) = delete;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }

    KruskalMinSpanningGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id].get(); }
    KruskalMinSpanningGraphEdge* get_edge(edgeid_t id) const override { return edges_[id].get(); }

    void add_vertex(vertexid_t id) override
    {
        vertices_.push_back(std::make_unique<KruskalMinSpanningGraphVertex>(id));
    }
    edgeid_t add_edge(edgeid_t id,
                      KruskalMinSpanningGraphVertex* u,
                      KruskalMinSpanningGraphVertex* v,
                      int32_t cost) override
    {
        edges_.push_back(std::make_unique<KruskalMinSpanningGraphEdge>(id, u, v, cost));
        ++id;
        return id;
    }

    long find_mst();
    unsigned int cluster(unsigned int k_cluster);

private:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

    KruskalMinSpanningGraphVertex* find_leader(KruskalMinSpanningGraphVertex* vertex);
    void union_leaders(KruskalMinSpanningGraphVertex* u, KruskalMinSpanningGraphVertex* v);

private:
    std::vector<std::unique_ptr<KruskalMinSpanningGraphVertex>> vertices_;
    std::vector<std::unique_ptr<KruskalMinSpanningGraphEdge>> edges_;
};

} // namespace Ps::Algo
