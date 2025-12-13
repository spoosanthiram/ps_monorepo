#pragma once

#include "algo/graph/Graph.h"

namespace Ps::Algo {

class AllPairShortestPathGraphEdge : public Edge<Vertex>
{
public:
    AllPairShortestPathGraphEdge(edgeid_t id, Vertex* u, Vertex* v, int cost)
        : Edge<Vertex>{id, u, v}
        , cost_{cost}
    {}

    int get_cost() const { return cost_; }

    void set_cost(int cost) { cost_ = cost; }

private:
    int cost_;
};

class AllPairShortestPathGraph : public Graph<Vertex, AllPairShortestPathGraphEdge>
{
public:
    AllPairShortestPathGraph() = default;
    ~AllPairShortestPathGraph();

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    Vertex* get_vertex(vertexid_t id) const override { return vertices_[id]; }
    AllPairShortestPathGraphEdge* get_edge(edgeid_t id) const override { return edges_[id]; }

    void add_vertex(vertexid_t id) override
    {
        auto v = new Vertex{id};
        vertices_.push_back(v);
    }
    edgeid_t add_edge(edgeid_t id, Vertex* u, Vertex* v, int32_t cost) override
    {
        auto e = new AllPairShortestPathGraphEdge{id, u, v, cost};
        edges_.push_back(e);

        return id + 1;
    }

    bool do_floyd_warshall(std::vector<int>& path_cost_matrix);

protected:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

private:
    std::vector<Vertex*> vertices_{};
    std::vector<AllPairShortestPathGraphEdge*> edges_{};
};

} // namespace Ps::Algo
