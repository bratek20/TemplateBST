#ifndef BST_BASE_H
#define BST_BASE_H

#include <functional>

namespace struktury {

template< typename T, class Cmp = std::less_equal<T> >
class BST {
    struct Node {
        Node(const T& val) : value(val) {}
        ~Node() {
            delete left;
            delete right;
        }

        Node* copy() {
            Node* res = new Node(value);
            if (left) res->left = left->copy();
            if (right) res->right = right->copy();

            return res;
        }

        bool leaf() {
            return !left && !right;
        }

        void remove(Node* node) {
            if (left == node) {
                left = node->right;
                node->right = nullptr;
                delete node;
            }
            else if (right == node) {
                right = node->right;
                node->right = nullptr;
                delete node;
            }
        }

        friend std::ostream& operator<<(std::ostream& out, Node* node) {
            if (node->left != nullptr) out << "(" << node->left << ")";
            out << node->value;
            if (node->right != nullptr) out << "(" << node->right << ")";

            return out;
        }

        T value;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    Node* root = nullptr;

public:
    BST() {}
    BST(std::initializer_list<T> list) {
        for (auto& elem : list)
            add(elem);
    }

    ~BST() {
        delete root;
    }

    BST(const BST& bst);
    BST(BST&& bst);

    BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);

    void add(const T& elem);
    void remove(const T& elem);
    bool exsist(const T& elem);

    friend std::ostream& operator<<(std::ostream& out, const BST<T, Cmp>& bst) {
        if (bst.root) {
            out << bst.root;
        }
        
        return out;
    }

private:
    bool comp(const T& e1, const T& e2);

    std::pair<Node*, Node*> findNode(Node* node, const T& elem, Node* parent = nullptr);
    void exception(const char* message);

    void removeLeaf(Node* leaf, Node* parent);
    void removeNoLeft(Node* node, Node* parent);
    void removeBySwapMax(Node* node);
};

}

#endif