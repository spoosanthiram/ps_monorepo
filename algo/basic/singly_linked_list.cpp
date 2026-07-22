#include "singly_linked_list.h"

namespace ps::algo {

SinglyLinkedList::~SinglyLinkedList()
{
    while (head_) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

uint32_t SinglyLinkedList::count_nodes() const
{
    uint32_t size = 0;

    Node* node = head_;
    while (node) {
        ++size;
        node = node->next;
    }

    return size;
}

std::vector<int> SinglyLinkedList::to_vector(int32_t num_elements) const
{
    std::vector<int> vec;
    Node* node = head_;
    while (node && num_elements > 0) {
        vec.push_back(node->data);
        node = node->next;
        --num_elements;
    }
    return vec;
}

SinglyLinkedList::Node* SinglyLinkedList::insert(int value)
{
    Node* node = new Node{value};
    if (head_) {
        node->next = head_;
        head_ = node;
    }
    else {
        head_ = node;
    }
    return node;
}

SinglyLinkedList::Node* SinglyLinkedList::insert_after(Node* node, int value)
{
    Node* new_node = new Node{value};
    insert_after(node, new_node);
    return new_node;
}

void SinglyLinkedList::insert_after(Node* node, Node* new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

void SinglyLinkedList::merge(SinglyLinkedList& other)
{
    if (!head_ && !other.head_) {
        return;
    }

    Node* new_head = nullptr;

    Node** tail = &new_head;
    while (head_ && other.head_) {
        Node*& node = (head_->data < other.head_->data) ? head_ : other.head_;
        *tail = node;
        node = node->next;

        tail = &(*tail)->next;
    }

    *tail = head_ ? head_ : other.head_;

    other.head_ = nullptr;
    head_ = new_head;
}

void SinglyLinkedList::reverse()
{
    Node* prev_node = nullptr;
    Node* node = head_;
    while (node) {
        Node* nn = node->next; // save next node
        node->next = prev_node;
        prev_node = node;
        node = nn;
    }
    head_ = prev_node;
}

bool SinglyLinkedList::operator==(const SinglyLinkedList& rhs) const
{
    auto lnode = head_;
    auto rnode = rhs.head_;
    while (lnode && rnode) {
        if (lnode->data != rnode->data) {
            return false;
        }
        lnode = lnode->next;
        rnode = rnode->next;
    }

    if (lnode || rnode) {
        return false;
    }

    return true;
}

} // namespace ps::algo
