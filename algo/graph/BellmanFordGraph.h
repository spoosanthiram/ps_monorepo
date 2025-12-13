#pragma once

#include "algo/graph/Graph.h"

namespace Ps::Algo {

class BellmanFordGraphEdge;

class BellmanFordGraphVertex : public Vertex
{
public:
    BellmanFordGraphVertex(vertexid_t id)
        : Vertex{id}
    {}

    const std::vector<BellmanFordGraphEdge*>& in_edges() const { return in_edges_; }

    void add_in_edge(BellmanFordGraphEdge* edge) { in_edges_.push_back(edge); }

private:
    std::vector<BellmanFordGraphEdge*> in_edges_{};
};

class BellmanFordGraphEdge : public Edge<BellmanFordGraphVertex>
{
public:
    BellmanFordGraphEdge(edgeid_t id, BellmanFordGraphVertex* u, BellmanFordGraphVertex* v, int cost)
        : Edge<BellmanFordGraphVertex>{id, u, v}
        , cost_{cost}
    {}

    int cost() const { return cost_; }

    void setcost(int cost) { cost_ = cost; }

private:
    int cost_;
};

class BellmanFordGraph : public Graph<BellmanFordGraphVertex, BellmanFordGraphEdge>
{
public:
    BellmanFordGraph() = default;
    ~BellmanFordGraph();

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    BellmanFordGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id]; }
    BellmanFordGraphEdge* get_edge(edgeid_t id) const override { return edges_[id]; }

    void add_vertex(vertexid_t id) override
    {
        auto v = new BellmanFordGraphVertex{id};
        vertices_.push_back(v);
    }
    edgeid_t add_edge(edgeid_t id, BellmanFordGraphVertex* u, BellmanFordGraphVertex* v, int32_t cost) override
    {
        auto e = new BellmanFordGraphEdge{id, u, v, cost};
        edges_.push_back(e);
        ++id;

        v->add_in_edge(e);

        return id;
    }

    bool find_shortest_path(vertexid_t source_vertex_id, std::vector<int>& cost);

protected:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

private:
    bool inner_iteration(std::vector<int>& cost, std::vector<int>& prev_cost);

    std::vector<BellmanFordGraphVertex*> vertices_{};
    std::vector<BellmanFordGraphEdge*> edges_{};
};

} // namespace Ps::Algo
