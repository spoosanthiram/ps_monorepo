#include "algo/graph/BreadthFirstGraph.h"

#include <format>
#include <queue>

namespace Ps::Algo {

std::string BreadthFirstGraphVertex::to_string() const
{
    std::string str;
    std::format_to(std::back_inserter(str), "{}", id());
    for (const auto edge : edges_) {
        if (edge->v()->id() > id()) {
            std::format_to(std::back_inserter(str), "{}{}", kSeparator, edge->v()->id());
        }
    }
    return str;
}

void BreadthFirstGraph::traverse(vertexid_t start_vertex_id)
{
    auto u = get_vertex(start_vertex_id);
    u->set_explored(true);

    std::queue<BreadthFirstGraphVertex*> queue;
    queue.push(u);

    while (!queue.empty()) {
        u = queue.front();
        queue.pop();

        for (auto e : u->edges()) {
            auto v = e->v();
            if (!v->is_explored()) {
                v->set_explored(true);
                queue.push(v);
            }
        }
    }
}

int32_t BreadthFirstGraph::find_distance(vertexid_t start_vertex_id, vertexid_t end_vertex_id)
{
    auto u = get_vertex(start_vertex_id);
    u->set_explored(true);
    u->set_distance(0);

    auto end = get_vertex(end_vertex_id);

    std::queue<BreadthFirstGraphVertex*> queue;
    queue.push(u);

    while (!queue.empty()) {
        u = queue.front();
        queue.pop();

        if (u->id() == end->id()) {
            break;
        }

        for (auto e : u->edges()) {
            auto v = e->v();
            if (!v->is_explored()) {
                v->set_explored(true);
                v->set_distance(u->distance() + 1);
                queue.push(v);
            }
        }
    }

    return end->distance();
}

} // namespace Ps::Algo
