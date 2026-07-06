#include "trie.h"

#include <stdexcept>

namespace ps::algo {

void Trie::insert(const std::string& key, int value)
{
    if (value == no_value) {
        throw std::invalid_argument{"Invalid value"};
    }

    Node* node = root_;
    for (char ch : key) {
        ch = ch - 'a';
        if (ch < 0 || ch >= alphabet_size) {
            throw std::invalid_argument{"Key needs to be in lower case alphabet"};
        }

        if (node->link[ch]) {
            node = node->link[ch];
        }
        else {
            node->link[ch] = new Node{};
            node = node->link[ch];
        }
    }
    node->value = value;
}

Trie::Node* Trie::get_node(const std::string& key) const
{
    Node* node = root_;
    char ch;
    for (std::size_t i = 0; node && i < key.size(); ++i) {
        ch = key[i] - 'a';
        if (ch < 0 || ch >= alphabet_size) {
            throw std::invalid_argument{"Key needs to be in lower case alphabet"};
        }
        node = node->link[ch];
    }
    return node;
}

void Trie::keys_with_prefix(Node* node, std::string key, std::vector<std::string>& result) const
{
    if (node == nullptr) {
        return;
    }

    if (node->value != no_value) {
        result.push_back(key);
    }

    for (char i = 0; i < alphabet_size; ++i) {
        if (node->link[i]) {
            std::string newKey = key;
            newKey += ('a' + i);
            keys_with_prefix(node->link[i], newKey, result);
        }
    }
}

} // namespace ps::algo
