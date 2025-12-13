#include "BitVertexClusteringGraph.h"

#include <forward_list>
#include <regex>

namespace Ps::Algo {

BitVertexClusteringGraph::~BitVertexClusteringGraph()
{
    for (auto vertex : vertices_) {
        delete vertex;
    }
}

void BitVertexClusteringGraph::read(std::istream& input_stream)
{
    const auto pattern = std::regex{R"(\s+)"};

    std::string line;
    std::getline(input_stream, line); // read # vertices and # bits

    auto it = std::sregex_token_iterator{line.begin(), line.end(), pattern, -1};
    vertices_.reserve(std::stoi(it->str()));

    std::sregex_token_iterator endIt;
    int vertexValue{0};

    while (input_stream) {
        std::getline(input_stream, line);
        if (line.size() == 0) {
            continue;
        }

        vertexValue = 0;

        it = std::sregex_token_iterator{line.begin(), line.end(), pattern, -1};
        std::string str;
        for (; it != endIt; ++it) {
            str = it->str();

            vertexValue <<= 1;

            if (str == "1") {
                vertexValue |= 0x1;
            }
        }

        vertices_.push_back(new BitVertexClusteringGraphVertex{vertexValue});
    }
}

void BitVertexClusteringGraph::build_edges()
{
    std::vector<BitVertexClusteringGraphEdge*> dist0Edges;
    std::vector<BitVertexClusteringGraphEdge*> dist1Edges;
    std::vector<BitVertexClusteringGraphEdge*> dist2Edges;

    for (auto it = vertices_.begin(); it != vertices_.end(); ++it) {
        for (auto it2 = it + 1; it2 != vertices_.end(); ++it2) {
            const auto distance = hamming_distance(*it, *it2);
            if (distance == 0) {
                dist0Edges.push_back(new BitVertexClusteringGraphEdge{*it, *it2});
            }
            else if (distance == 1) {
                dist1Edges.push_back(new BitVertexClusteringGraphEdge{*it, *it2});
            }
            else if (distance == 2) {
                dist2Edges.push_back(new BitVertexClusteringGraphEdge{*it, *it2});
            }
        }
    }

    edges_.reserve(dist0Edges.size() + dist1Edges.size() + dist2Edges.size());

    std::copy(dist0Edges.begin(), dist0Edges.end(), std::back_inserter(edges_));
    std::copy(dist1Edges.begin(), dist1Edges.end(), std::back_inserter(edges_));
    std::copy(dist2Edges.begin(), dist2Edges.end(), std::back_inserter(edges_));
}

int BitVertexClusteringGraph::cluster()
{
    auto ncluster = static_cast<int>(vertices_.size());

    for (auto edge : edges_) {
        auto uleader = find_leader(edge->u);
        auto vleader = find_leader(edge->v);
        if (uleader != vleader) {
            union_leaders(uleader, vleader);
            --ncluster;
        }
    }

    return ncluster;
}

BitVertexClusteringGraphVertex* BitVertexClusteringGraph::find_leader(BitVertexClusteringGraphVertex* v)
{
    if (v->leader == v || v->leader->leader == v->leader) {
        return v->leader;
    }

    std::forward_list<BitVertexClusteringGraphVertex*> vertices;
    while (v->leader != v) {
        vertices.push_front(v);
        v = v->leader;
    }

    vertices.pop_front();
    for (auto u : vertices) {
        u->leader = v;
    }

    return v;
}

void BitVertexClusteringGraph::union_leaders(BitVertexClusteringGraphVertex* u, BitVertexClusteringGraphVertex* v)
{
    if (u->rank > v->rank) {
        v->leader = u;
    }
    else if (u->rank < v->rank) {
        u->leader = v;
    }
    else {
        u->rank = u->rank + 1;
        v->leader = u;
    }
}

} // namespace Ps::Algo
