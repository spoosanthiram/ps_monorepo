#pragma once

#include <array>
#include <string>
#include <vector>

namespace Ps::Algo {

constexpr auto kAlphabet_Size = 26;
constexpr auto kNo_Value = -1;

class Trie
{
public:
    struct Node
    {
        Node(int val = kNo_Value)
            : value{val}
        {
            link.fill(nullptr);
        }
        int value;
        std::array<Node*, kAlphabet_Size> link;
    };

public:
    Trie() { root_ = new Node{}; }

    int value(const std::string& key) const
    {
        Node* node = get_node(key);
        return node ? node->value : kNo_Value;
    }
    std::vector<std::string> keys_with_prefix(const std::string& prefix) const
    {
        std::vector<std::string> result;
        keys_with_prefix(get_node(prefix), prefix, result);
        return result;
    }

    void insert(const std::string& key, int value);

private:
    Node* get_node(const std::string& key) const;
    void keys_with_prefix(Node* node, std::string key, std::vector<std::string>& result) const;

private:
    Node* root_;
};

} // namespace Ps::Algo
