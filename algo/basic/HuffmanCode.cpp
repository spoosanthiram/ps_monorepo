#include "algo/basic/HuffmanCode.h"

namespace Ps::Algo {

void HuffTree::build(std::istream& stream)
{
    auto symbols = read_symbols(stream);

    less_than_t lt_lambda = [](HuffNode* x, HuffNode* y) -> bool { return x->data.frequency < y->data.frequency; };
    min_heap_ = new MinHeap<HuffNode*, less_than_t, NullIndex<HuffNode*>>(
        build_nodes(symbols), lt_lambda, NullIndex<HuffNode*>{});

    while (min_heap_->size() > 1) {
        HuffNode* right_node = min_heap_->pop();
        HuffNode* left_node = min_heap_->pop();

        HuffNode* node = new HuffNode{
            HuffData{0, left_node->data.frequency + right_node->data.frequency}
        };
        node->left = left_node;
        node->right = right_node;

        min_heap_->push(node);
    }
}

void HuffTree::encode()
{
    encode(min_heap_->top(), std::string{});
}

void HuffTree::print_codes(std::ostream& stream)
{
    print_codes(min_heap_->top(), stream);
}

std::vector<HuffData> HuffTree::read_symbols(std::istream& stream)
{
    constexpr auto kMax_Symbols = 255;

    std::vector<HuffData> symbols;
    symbols.reserve(kMax_Symbols + 1);

    for (int i = 0; i <= kMax_Symbols; ++i) {
        symbols.emplace_back(i);
    }

    char ch;
    while (stream.get(ch)) {
        if (ch < 0 || static_cast<int>(ch) >= kMax_Symbols) {
            throw std::runtime_error{"Character not supported currently!"};
        }

        ++(symbols[ch].frequency);
    }

    auto it = std::remove_if(symbols.begin(), symbols.end(), [](const HuffData& x) { return x.frequency == 0; });
    symbols.erase(it, symbols.end());

    return symbols;
}

std::vector<HuffNode*> HuffTree::build_nodes(const std::vector<HuffData>& symbols)
{
    std::vector<HuffNode*> nodes;

    for (auto& data : symbols) {
        HuffNode* node = new HuffNode{data};
        nodes.push_back(node);
    }

    return nodes;
}

void HuffTree::encode(HuffNode* node, std::string code)
{
    if (!node) {
        return;
    }

    node->data.code = code;

    encode(node->left, code + "0");
    encode(node->right, code + "1");
}

void HuffTree::print_codes(HuffNode* node, std::ostream& stream)
{
    if (!node) {
        return;
    }

    std::string symbol;
    if (node->data.symbol != 0) {
        if (node->data.symbol == ' ') {
            symbol.assign("sp");
        }
        else if (node->data.symbol == '\n') {
            symbol.assign("nl");
        }
        else if (node->data.symbol == '\t') {
            symbol.assign("tab");
        }
        else {
            symbol = node->data.symbol;
        }
        stream << symbol << " --> " << node->data.code << "\n";
    }

    print_codes(node->left, stream);
    print_codes(node->right, stream);
}

} // namespace Ps::Algo
