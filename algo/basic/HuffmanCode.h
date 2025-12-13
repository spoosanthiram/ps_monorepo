#pragma once

#include "algo/basic/MinHeap.h"

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace Ps::Algo {

struct HuffData
{
    HuffData(char sym)
        : symbol{sym}
    {}
    HuffData(char sym, unsigned int freq)
        : symbol{sym}
        , frequency{freq}
    {}
    char symbol;
    unsigned int frequency{0};
    std::string code;
};

struct HuffNode
{
    HuffNode(const HuffData& x)
        : data{x}
    {}
    HuffData data;
    HuffNode* left{nullptr};
    HuffNode* right{nullptr};
};

class HuffTree
{
public:
    using less_than_t = bool (*)(HuffNode* x, HuffNode* y);

public:
    HuffTree() = default;

    void build(std::istream& stream);
    void encode();
    void print_codes(std::ostream& stream);

private:
    std::vector<HuffData> read_symbols(std::istream& stream);
    std::vector<HuffNode*> build_nodes(const std::vector<HuffData>& symbols);
    void encode(HuffNode* node, std::string code);
    void print_codes(HuffNode* node, std::ostream& stream);

private:
    MinHeap<HuffNode*, less_than_t, NullIndex<HuffNode*>>* min_heap_;
};

} // namespace Ps::Algo
