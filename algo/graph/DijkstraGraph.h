#pragma once

#include "algo/graph/Graph.h"

#include <limits>
#include <vector>

namespace Ps::Algo {

class DijkstraGraphEdge;

class DijkstraGraphVertex : public Vertex
{
public:
    DijkstraGraphVertex(vertexid_t id)
        : Vertex{id}
    {}
    ~DijkstraGraphVertex() override = default;

    uint32_t distance() const { return distance_; }
    DijkstraGraphVertex* parent() const { return parent_; }
    const std::vector<DijkstraGraphEdge*>& edges() const { return edges_; }

    void set_distance(uint32_t distance) { distance_ = distance; }
    void set_parent(DijkstraGraphVertex* parent) { parent_ = parent; }

    void add_edge(DijkstraGraphEdge* edge) { edges_.push_back(edge); }

private:
    uint32_t distance_{std::numeric_limits<uint32_t>::max()};
    DijkstraGraphVertex* parent_{nullptr};
    std::vector<DijkstraGraphEdge*> edges_;
};

class DijkstraGraphEdge : public Edge<DijkstraGraphVertex>
{
public:
    DijkstraGraphEdge(edgeid_t id, DijkstraGraphVertex* u, DijkstraGraphVertex* v, uint32_t length);

    uint32_t length() const { return length_; }

    void set_length(uint32_t length) { length_ = length; }

private:
    uint32_t length_;
};

class DijkstraGraph : public Graph<DijkstraGraphVertex, DijkstraGraphEdge>
{
public:
    DijkstraGraph() = default;
    ~DijkstraGraph() override;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    DijkstraGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id]; }
    DijkstraGraphEdge* get_edge(edgeid_t id) const override { return edges_[id]; }

    void add_vertex(vertexid_t id) override
    {
        auto v = new DijkstraGraphVertex{id};
        vertices_.push_back(v);
    }
    edgeid_t add_edge(edgeid_t id, DijkstraGraphVertex* u, DijkstraGraphVertex* v, int32_t length) override
    {
        auto e = new DijkstraGraphEdge{id, u, v, static_cast<uint32_t>(length)};
        u->add_edge(e);
        edges_.push_back(e);
        ++id;

        if (type() == Type::Undirected) {
            e = new DijkstraGraphEdge{id, v, u, static_cast<uint32_t>(length)};
            v->add_edge(e);
            edges_.push_back(e);
            ++id;
        }

        return id;
    }

    void find_shortest_path(vertexid_t source_vertex_id);

private:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

    std::vector<DijkstraGraphVertex*> vertices_;
    std::vector<DijkstraGraphEdge*> edges_;
};

} // namespace Ps::Algo
