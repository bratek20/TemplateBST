#ifndef BST_BASE_IMPL_H
#define BST_BASE_IMPL_H

#include "BST_Base.h"

namespace struktury {

template< typename T, class Cmp>
BST<T, Cmp>::BST(const BST& bst) {
    if (!bst.root) {
        root = nullptr;
        return;
    }
    root = bst.root->copy();
}

template< typename T, class Cmp>
BST<T, Cmp>::BST(BST&& bst) {
    root = bst.root;
    bst.root = nullptr;

    return *this;
}

template< typename T, class Cmp>
BST<T, Cmp>& BST<T, Cmp>::operator=(const BST& bst) {
    if (this == &bst) {
        return *this;
    }

    delete this;

    BST tmp(bst);
    *this = std::move(tmp);

    return *this;
}

template< typename T, class Cmp>
BST<T, Cmp>& BST<T, Cmp>::operator=(BST&& bst) {
    delete this;

    root = bst.root;
    bst.root = nullptr;

    return *this;
}

template< typename T, class Cmp>
bool BST<T, Cmp>::comp(const T& e1, const T& e2) {
    return Cmp()(e1, e2);
}

template< typename T, class Cmp>
std::pair<typename BST<T, Cmp>::Node*, typename BST<T, Cmp>::Node*> BST<T, Cmp>::findNode(Node* node, const T& elem, Node* parent) {
    if (comp(node->value, elem) && comp(elem, node->value)) { // elem == value
        return std::make_pair(node, parent);
    }

    if (comp(elem, node->value)) { // elem < value
        if (node->left) {
            return findNode(node->left, elem, node);
        }
        return std::make_pair(nullptr, node);
    }

    if (comp(node->value, elem)) { // value < elem
        if (node->right) {
            return findNode(node->right, elem, node);
        }
        return std::make_pair(nullptr, node);
    }

    exception("BST::findNode | Bad order");
    return std::make_pair(nullptr, nullptr);
}

template< typename T, class Cmp>
void BST<T, Cmp>::exception(const char* message) {
    throw std::exception(message);
}

template< typename T, class Cmp>
void BST<T, Cmp>::add(const T& elem) {
    if (root == nullptr) {
        root = new Node(elem);
        return;
    }

    auto pair = findNode(root, elem);
    if (pair.first != nullptr) {
        return;
    }

    auto parent = pair.second;
    if (comp(elem, parent->value)) {
        parent->left = new Node(elem);
        return;
    }
    if (comp(parent->value, elem)) {
        parent->right = new Node(elem);
        return;
    }

    exception("BST::add | Bad order");
}

template< typename T, class Cmp>
void BST<T, Cmp>::remove(const T& elem) {
    if (!root) {
        return;
    }

    auto pair = findNode(root, elem);
    if (pair.first == nullptr) {
        return; // not found
    }

    auto node = pair.first;
    auto parent = pair.second;
    if (node->leaf()) {
        removeLeaf(node, parent);
        return;
    }

    if (!node->left) {
        removeNoLeft(node, parent);
        return;
    }

    removeBySwapMax(node);
}

template< typename T, class Cmp>
void BST<T, Cmp>::removeLeaf(Node* leaf, Node* parent) {
    if (parent == nullptr) { //we delete root
        delete leaf;
        root = nullptr;
        return;
    }

    parent->remove(leaf);
}

template< typename T, class Cmp>
void BST<T, Cmp>::removeNoLeft(Node* node, Node* parent) {
    if (!parent) { // node == root
        root = node->right;
        node->right = nullptr;
        delete node;
        return;
    }

    parent->remove(node);
}

template< typename T, class Cmp>
void BST<T, Cmp>::removeBySwapMax(Node* node) {
    Node* tmp = node->left;
    Node* parent = node;

    if (!tmp->right) {
        node->value = tmp->value;
        node->left = tmp->left;
        tmp->left = nullptr;
        
        delete tmp;
        return;
    }

    parent = tmp;
    tmp = tmp->right;
    while (!tmp->leaf()) {
        parent = tmp;
        if (tmp->right)
            tmp = tmp->right;
        else
            tmp = tmp->left;
    }

    node->value = tmp->value;

    parent->remove(tmp);
}

template< typename T, class Cmp>
bool BST<T, Cmp>::exsist(const T& elem) {
    return findNode(root, elem).first != nullptr;
}

}
#endif