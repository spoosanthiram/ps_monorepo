#include "algo/graph/Graph.h"

#include <memory>
#include <vector>

namespace Ps::Algo {

class BreadthFirstGraphVertex : public Vertex
{
public:
    BreadthFirstGraphVertex(vertexid_t id)
        : Vertex{id}
    {}
    ~BreadthFirstGraphVertex() override = default;

    std::string to_string() const override;
    bool is_explored() const { return explored_; }
    int32_t distance() const { return distance_; }
    const std::vector<Edge<BreadthFirstGraphVertex>*>& edges() const { return edges_; }

    void set_explored(bool explored) { explored_ = explored; }
    void set_distance(int32_t distance) { distance_ = distance; }

    void add_edge(Edge<BreadthFirstGraphVertex>* e) { edges_.push_back(e); }

private:
    bool explored_{false};
    int32_t distance_{-1};
    std::vector<Edge<BreadthFirstGraphVertex>*> edges_;
};

class BreadthFirstGraph : public Graph<BreadthFirstGraphVertex, Edge<BreadthFirstGraphVertex>>
{
public:
    BreadthFirstGraph() = default;
    ~BreadthFirstGraph() override = default;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    BreadthFirstGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id].get(); }
    Edge<BreadthFirstGraphVertex>* get_edge(edgeid_t id) const override { return edges_[id].get(); }

    void add_vertex(vertexid_t id) override { vertices_.push_back(std::make_unique<BreadthFirstGraphVertex>(id)); }
    edgeid_t add_edge(edgeid_t id, BreadthFirstGraphVertex* u, BreadthFirstGraphVertex* v, int32_t /*value*/) override
    {
        edges_.push_back(std::make_unique<Edge<BreadthFirstGraphVertex>>(id, u, v));
        u->add_edge(edges_.back().get());
        ++id;

        if (type() == Type::Undirected) {
            edges_.push_back(std::make_unique<Edge<BreadthFirstGraphVertex>>(id, v, u));
            v->add_edge(edges_.back().get());
            ++id;
        }

        return id;
    }

    void traverse(vertexid_t start_vertex_id);
    int32_t find_distance(vertexid_t start_vertex_id, vertexid_t end_vertex_id);

private:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override { edges_.reserve(num_edges); }

    std::vector<std::unique_ptr<BreadthFirstGraphVertex>> vertices_;
    std::vector<std::unique_ptr<Edge<BreadthFirstGraphVertex>>> edges_;
};

} // namespace Ps::Algo
