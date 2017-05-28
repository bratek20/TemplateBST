#ifndef BST_CSTR_SPEC_H
#define BST_CSTR_SPEC_H

#include "BST_BaseImpl.h"
#include <string.h>
#include <string>

namespace struktury {

template<typename Cmp>
class BST<const char*, Cmp> : BST<std::string, Cmp> {
    using Cstr = const char*;
public:
    BST() = default;
    BST(std::initializer_list<const char*> list) : BST<std::string, Cmp>() {
        for (auto elem : list)
            add(elem);
    }

    void add(Cstr elem) {
        BST<std::string, Cmp>::add(std::string(elem));
    }

    void remove(Cstr elem) {
        BST<std::string, Cmp>::remove(std::string(elem));
    }

    bool exsist(Cstr elem) {
        return BST<std::string, Cmp>::exsist(std::string(elem));
    }

    friend std::ostream& operator<<(std::ostream& out, const BST<Cstr, Cmp>& bst) {
        out << static_cast<BST<std::string, Cmp>>(bst);
        return out;
    }
};


struct DefaultCStrCmp {
    bool operator()(const std::string& s1, const std::string& s2) { // <=
        return strcmp(s1.c_str(), s2.c_str()) != 1;
    }
};

template<>
class BST<const char*> : public BST<const char*, DefaultCStrCmp > {
public:
    BST() = default;
    BST(std::initializer_list<const char*> list) : BST<const char*, DefaultCStrCmp>(list) {}
};
    
}

#endif