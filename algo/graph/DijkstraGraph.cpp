#include "algo/graph/DijkstraGraph.h"

#include "algo/basic/MinHeap.h"

#include <format>

namespace Ps::Algo {

// LessThan function type, used for less than compare function on Dijkstra vertices
using LessThan = bool (*)(DijkstraGraphVertex*, DijkstraGraphVertex*);

DijkstraGraphEdge::DijkstraGraphEdge(edgeid_t id, DijkstraGraphVertex* u, DijkstraGraphVertex* v, unsigned int length)
    : Edge<DijkstraGraphVertex>{id, u, v}
    , length_{length}
{}

DijkstraGraph::~DijkstraGraph()
{
    for (auto edge : edges_) {
        delete edge;
    }

    for (auto vertex : vertices_) {
        delete vertex;
    }
}

void DijkstraGraph::find_shortest_path(vertexid_t source_vertex_id)
{
    DijkstraGraphVertex* source_vertex = get_vertex(source_vertex_id);
    if (source_vertex == nullptr) {
        throw std::runtime_error{std::format("Source vertex id, {} is not in the graph!", source_vertex_id)};
    }

    source_vertex->set_distance(0);

    std::unordered_map<vertexid_t, std::size_t> heap_index_map; // vertices to MinHeap index map

    // compare function of type Compare
    auto less_than = [](DijkstraGraphVertex* lhs, DijkstraGraphVertex* rhs) -> bool {
        return lhs->distance() < rhs->distance();
    };

    // the index done through heap indexing functor
    MinHeap<DijkstraGraphVertex*, LessThan, HeapIndex<DijkstraGraphVertex>> vertices_to_process{
        vertices_, less_than, HeapIndex<DijkstraGraphVertex>{heap_index_map}};

    std::vector<DijkstraGraphVertex*> processed_vertices{vertices_.size()}; // fill it with nullptr

    while (!vertices_to_process.is_empty()) {
        DijkstraGraphVertex* v = vertices_to_process.pop();

        processed_vertices[v->id()] = v;

        for (auto e : v->edges()) {
            DijkstraGraphVertex* w = e->v();
            if (!processed_vertices[w->id()]) {
                if (v->distance() + e->length() < w->distance()) {
                    w->set_distance(v->distance() + e->length());
                    w->set_parent(v);
                    vertices_to_process.sift_up(heap_index_map[w->id()]);
                }
            }
        }
    }
}

} // namespace Ps::Algo
