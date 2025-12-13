#include "SinglyLinkedList.h"

namespace Ps::Algo {

SinglyLinkedList::~SinglyLinkedList()
{
    while (head_) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

size_t SinglyLinkedList::count_nodes() const
{
    size_t size = 0;

    Node* node = head_;
    while (node) {
        ++size;
        node = node->next;
    }

    return size;
}

void SinglyLinkedList::insert(int value)
{
    Node* node = new Node{value};
    if (head_) {
        node->next = head_;
        head_ = node;
    }
    else {
        head_ = node;
    }
}

void SinglyLinkedList::insert_after(Node* node, int value)
{
    Node* new_node = new Node{value};
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
    Node* next_node = nullptr;
    Node* node = head_;
    while (node) {
        next_node = node->next;
        node->next = prev_node;
        prev_node = node;
        node = next_node;
    }
    head_ = prev_node;
}

bool SinglyLinkedList::operator==(const SinglyLinkedList& rhs) const
{
    bool retval = true;

    Node* lnode = head_;
    Node* rnode = rhs.head_;
    while (lnode && rnode) {
        if (lnode->data != rnode->data) {
            retval = false;
            break;
        }
        lnode = lnode->next;
        rnode = rnode->next;
    }

    if (retval && (lnode || rnode)) {
        retval = false;
    }

    return retval;
}

} // namespace Ps::Algo
