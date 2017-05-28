#ifndef BST_PTR_SPEC_H
#define BST_PTR_SPEC_H

#include "BST_BaseImpl.h"

namespace struktury {

template< typename T, typename Cmp>
class BST<T*, Cmp> : BST<T, Cmp> {
public:
    BST() = default;
    BST(std::initializer_list<T*> list) : BST<T, Cmp>() {}

    void add(T* elem) {
        BST<T, Cmp>::add(*elem);
    }

    void remove(T* elem) {
        BST<T, Cmp>::remove(*elem);
    }

    bool exsist(T* elem) {
        return BST<T, Cmp>::exsist(*elem);
    }

    friend std::ostream& operator<<(std::ostream& out, const BST<T*, Cmp>& bst) {
        out << static_cast<BST<T, Cmp>>(bst);
        return out;
    }
};

template< typename T>
class BST<T*> : public BST<T*, std::less_equal<T> > {
public:
    BST() = default;
    BST(std::initializer_list<T*> list) : BST<T*, std::less_equal<T> >() {}
};

}

#endif