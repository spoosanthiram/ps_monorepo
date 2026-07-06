#pragma once

#include <array>
#include <string>
#include <vector>

namespace ps::algo {

constexpr auto alphabet_size = 26;
constexpr auto no_value = -1;

class Trie
{
public:
    struct Node
    {
        Node(int val = no_value)
            : value{val}
        {
            link.fill(nullptr);
        }
        int value;
        std::array<Node*, alphabet_size> link;
    };

public:
    Trie() { root_ = new Node{}; }

    int value(const std::string& key) const
    {
        Node* node = get_node(key);
        return node ? node->value : no_value;
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

} // namespace ps::algo
