#pragma once

#include "algo/graph/Graph.h"
#include "core/utils/ClassHelper.h"

#include <memory>
#include <vector>

namespace Ps::Algo {

class StronglyConnectedGraphVertex : public Vertex
{
public:
    StronglyConnectedGraphVertex(vertexid_t id)
        : Vertex{id}
    {}
    ~StronglyConnectedGraphVertex() override = default;

    bool explored() const { return explored_; }
    int finish_time() const { return finish_time_; }
    StronglyConnectedGraphVertex* leader() const { return leader_; }
    const std::vector<Edge<StronglyConnectedGraphVertex>*>& edges() const { return edges_; }
    const std::vector<Edge<StronglyConnectedGraphVertex>*>& reverse_edges() const { return reverse_edges_; }

    void set_explored(bool explored) { explored_ = explored; }
    void set_finish_time(int time) { finish_time_ = time; }
    void set_leader(StronglyConnectedGraphVertex* leader) { leader_ = leader; }

    void add_edge(Edge<StronglyConnectedGraphVertex>* e) { edges_.push_back(e); }
    void add_reverse_edge(Edge<StronglyConnectedGraphVertex>* e) { reverse_edges_.push_back(e); }

private:
    bool explored_{false};
    int32_t finish_time_{-1};
    StronglyConnectedGraphVertex* leader_{nullptr};
    std::vector<Edge<StronglyConnectedGraphVertex>*> edges_;
    std::vector<Edge<StronglyConnectedGraphVertex>*> reverse_edges_;
};

class StronglyConnectedGraph : public Graph<StronglyConnectedGraphVertex, Edge<StronglyConnectedGraphVertex>>
{
public:
    StronglyConnectedGraph() = default;
    ~StronglyConnectedGraph() override = default;

    COPY_CONSTRUCTOR(StronglyConnectedGraph) = delete;
    MOVE_CONSTRUCTOR(StronglyConnectedGraph) = delete;
    COPY_ASSIGNMENT(StronglyConnectedGraph) = delete;
    MOVE_ASSIGNMENT(StronglyConnectedGraph) = delete;

    vertexid_t vertices_size() const override { return static_cast<vertexid_t>(vertices_.size()); }
    edgeid_t edges_size() const override { return edges_.size(); }
    StronglyConnectedGraphVertex* get_vertex(vertexid_t id) const override { return vertices_[id].get(); }
    Edge<StronglyConnectedGraphVertex>* get_edge(edgeid_t id) const override { return edges_[id].get(); }

    void add_vertex(vertexid_t id) override { vertices_.push_back(std::make_unique<StronglyConnectedGraphVertex>(id)); }
    edgeid_t add_edge(edgeid_t id,
                      StronglyConnectedGraphVertex* u,
                      StronglyConnectedGraphVertex* v,
                      int32_t /*value*/) override;

    /// @brief StronglyConnectedGraph::kosaraju computes strongly connected components (SCC) for the
    /// graph using Kosaraju's algorithm.
    /// @return unordered_map that maps leader vertex id to size of SCC.
    ///
    std::unordered_map<vertexid_t, uint32_t> kosaraju();

private:
    void reserve_vertices(vertexid_t num_vertices) override { vertices_.reserve(num_vertices); }
    void reserve_edges(edgeid_t num_edges) override
    {
        edges_.reserve(num_edges);
        reverse_edges_.reserve(num_edges);
    }

    void dfs_loop_reverse();
    void dfs_reverse(StronglyConnectedGraphVertex* v);
    void dfs_loop();
    void dfs(StronglyConnectedGraphVertex* v, StronglyConnectedGraphVertex* leader);

    int32_t next_finish_time() { return finish_time_++; }

private:
    std::vector<std::unique_ptr<StronglyConnectedGraphVertex>> vertices_;
    std::vector<std::unique_ptr<Edge<StronglyConnectedGraphVertex>>> edges_;
    std::vector<std::unique_ptr<Edge<StronglyConnectedGraphVertex>>> reverse_edges_;

    // transient states
    int32_t finish_time_ = 0;
    std::vector<StronglyConnectedGraphVertex*> vertices_by_finish_time_;
};

} // namespace Ps::Algo
