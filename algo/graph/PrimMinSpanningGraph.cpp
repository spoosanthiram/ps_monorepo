#include "algo/graph/PrimMinSpanningGraph.h"

#include "algo/basic/MinHeap.h"

namespace Ps::Algo {

// LessThan function type, for less than compare function on PrimMinSpanningGraphVertex
using LessThan = bool (*)(const PrimMinSpanningGraphVertex*, const PrimMinSpanningGraphVertex*);

PrimMinSpanningGraph::~PrimMinSpanningGraph()
{
    for (auto edge : edges_) {
        delete edge;
    }

    for (auto vertex : vertices_) {
        delete vertex;
    }
}

int64_t PrimMinSpanningGraph::find_mst()
{
    PrimMinSpanningGraphVertex* v = get_vertex(0); // some arbitrary vertex
    v->set_cost(0);

    int64_t cost = 0;
    std::unordered_map<vertexid_t, std::size_t> heap_index_map;

    // less than lambda
    auto less_than = [](const PrimMinSpanningGraphVertex* lhs, const PrimMinSpanningGraphVertex* rhs) -> bool {
        return lhs->cost() < rhs->cost();
    };

    MinHeap<PrimMinSpanningGraphVertex*, LessThan, HeapIndex<PrimMinSpanningGraphVertex>> vertices_to_process{
        vertices_, less_than, HeapIndex<PrimMinSpanningGraphVertex>{heap_index_map}};

    std::vector<PrimMinSpanningGraphVertex*> processed_vertices{vertices_.size()}; // fill with nullptr

    while (!vertices_to_process.is_empty()) {
        v = vertices_to_process.pop();

        processed_vertices[v->id()] = v;
        cost += v->cost();

        for (auto e : v->edges()) {
            PrimMinSpanningGraphVertex* w = e->v();
            if (!processed_vertices[w->id()]) {
                if (e->cost() < w->cost()) {
                    w->set_cost(e->cost());
                    vertices_to_process.sift_up(heap_index_map[w->id()]);
                }
            }
        }
    }

    return cost;
}

} // namespace Ps::Algo
