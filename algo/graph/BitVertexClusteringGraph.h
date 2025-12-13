#pragma once

#include <fstream>
#include <vector>

namespace Ps::Algo {

struct BitVertexClusteringGraphVertex
{
    BitVertexClusteringGraphVertex(int x)
        : bits{x}
        , leader{this}
    {}

    int bits;
    BitVertexClusteringGraphVertex* leader;
    int rank{0};
};

struct BitVertexClusteringGraphEdge
{
    BitVertexClusteringGraphEdge(BitVertexClusteringGraphVertex* x, BitVertexClusteringGraphVertex* y)
        : u{x}
        , v{y}
    {}
    BitVertexClusteringGraphVertex* u;
    BitVertexClusteringGraphVertex* v;
};

class BitVertexClusteringGraph
{
public:
    BitVertexClusteringGraph() = default;
    ~BitVertexClusteringGraph();

    void read(std::istream& input_stream);
    void build_edges();
    int cluster();

private:
    int hamming_distance(BitVertexClusteringGraphVertex* u, BitVertexClusteringGraphVertex* v)
    {
        int distance = 0;
        int xorValue = u->bits ^ v->bits;
        if (xorValue) {
            ++distance;
            xorValue &= (xorValue - 1);
        }
        if (xorValue) {
            ++distance;
            xorValue &= (xorValue - 1);
        }
        return xorValue ? 3 : distance;
    }

    BitVertexClusteringGraphVertex* find_leader(BitVertexClusteringGraphVertex* v);
    void union_leaders(BitVertexClusteringGraphVertex* u, BitVertexClusteringGraphVertex* v);

    std::vector<BitVertexClusteringGraphVertex*> vertices_{};
    std::vector<BitVertexClusteringGraphEdge*> edges_{};
};

} // namespace Ps::Algo
