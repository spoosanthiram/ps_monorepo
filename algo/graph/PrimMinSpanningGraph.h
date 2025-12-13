#pragma once

#include "algo/graph/Graph.h"
#include "core/utils/ClassHelper.h"

#include <limits>

namespace Ps::Algo {

class PrimMinSpanningGraphEdge;

class PrimMinSpanningGraphVertex : public Vertex
{
public:
    PrimMinSpanningGraphVertex(vertexid_t id)
        : Vertex{id}
    {}

    int32_t cost() const { return cost_; }
    const std::vector<PrimMinSpanningGraphEdge*>& edges() const { return edges_; }

    void set_cost(int32_t cost) { cost_ = cost; }

    void add_edge(PrimMinSpanningGraphEdge* e) { edges_.push_back(e); }

private:
    int32_t cost_{std::numeric_limits<int32_t>::max()};
    std::vector<PrimMinSpanningGraphEdge*> edges_;
};

class PrimMinSpanningGraphEdge : public Edge<PrimMinSpanningGraphVertex>
{
public:
    PrimMinSpanningGraphEdge(edgeid_t id, PrimMinSpanningGraphVertex* u, PrimMinSpanningGraphVertex* v, int32_t cost)
        : Edge<PrimMinSpanningGraphVertex>{id, u, v}
        , cost_{cost}
    {}

    int32_t cost() const { return cost_; }

private:
    int32_t cost_;
};

class PrimMinSpanningGraph : public Graph<PrimMinSpanningGraphVertex, PrimMinSpanningGraphEdge>
{
public:
    PrimMinSpanningGraph() = default;
    ~PrimMinSpanningGraph();

    COPY_CONSTRUCTOR(PrimMinSpanningGraph) = delete;
    MOVE_CONSTRUCTOR(PrimMinSpanningGraph) = delete;
    COPY_ASSIGNMENT(PrimMinSpanningGraph) = delete;
    MOVE_ASSIGNMENT(PrimMinSpanningGraph) = delete;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    PrimMinSpanningGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id]; }
    PrimMinSpanningGraphEdge* get_edge(edgeid_t id) const override { return edges_[id]; }

    void add_vertex(vertexid_t id) override
    {
        auto v = new PrimMinSpanningGraphVertex{id};
        vertices_.push_back(v);
    }
    edgeid_t add_edge(edgeid_t id, PrimMinSpanningGraphVertex* u, PrimMinSpanningGraphVertex* v, int32_t cost) override
    {
        auto e = new PrimMinSpanningGraphEdge{id, u, v, cost};
        u->add_edge(e);
        edges_.push_back(e);
        ++id;

        if (type() == Type::Undirected) {
            e = new PrimMinSpanningGraphEdge{id, v, u, cost};
            v->add_edge(e);
            edges_.push_back(e);
            ++id;
        }

        return id;
    }

    int64_t find_mst();

private:
    void reserve_vertices(vertexid_t nuvertices_) override { vertices_.reserve(nuvertices_); }
    void reserve_edges(edgeid_t nuedges_) override { edges_.reserve(nuedges_); }

private:
    std::vector<PrimMinSpanningGraphVertex*> vertices_;
    std::vector<PrimMinSpanningGraphEdge*> edges_;
};

} // namespace Ps::Algo
