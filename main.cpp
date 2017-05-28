#include "BST.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

using namespace struktury;
using namespace std;

template <typename T>
struct isString {
    static const bool value = false;
};

template <>
struct isString<char const*> {
    static const bool value = true;
};

std::string s;
istream& operator>>(istream& in, const char*& elem) {
    in >> s;
    
    const_cast<const char*>(elem) = s.c_str();

    return in;
}

template< typename T>
struct create {
    static T make() {
        return T{};
    }
};

template< typename T>
struct create<T*> {
    static T* make() {
        return new T;
    }
};

template<typename T>
struct removePtr {
    using type = T;
};
template<typename T>
struct removePtr<T*> {
    using type = T;
};
template<>
struct removePtr<const char*> {
    using type = int;
};

template <typename T>
struct initList {
    static const std::initializer_list<T> list;
};
template <typename T>
const std::initializer_list<T> initList<T>::list = { T{} };

template <typename T>
struct initList<T*> {
    static const std::initializer_list<T*> list;
};
template <typename T>
const std::initializer_list<T*> initList<T*>::list;

template <>
struct initList<int> {
    static const std::initializer_list<int> list;
};
const std::initializer_list<int>  initList<int>::list = { 5,3,7,8,1,42,666 };


template <>
struct initList<const char*> {
    static const std::initializer_list<const char*> list;
};
const std::initializer_list<const char*>  initList<const char*>::list = { "elo","elo","3","2","0","5","10","lol" };


using Type = const char*;
using NoPtr = removePtr<Type>::type;
NoPtr tab[100];
int idx = 0;

istream& operator >> (istream& in, NoPtr*& elem) {
    in >> tab[idx];
    elem = &tab[idx++];

    return in;
}

int main() {  
    BST<Type> bst = initList<Type>::list;
    string cmd;
    while (true) {
        cin >> cmd;
        if (cmd == "end")
            break;
        
        if (cmd == "out") {
            cout << bst << "\n";
            continue;
        }

        Type x = create<Type>::make();
        cin >> x;
        
        if (cmd == "add")
            bst.add(x);
        else if (cmd == "rem")
            bst.remove(x);
        else if (cmd == "ex")
            cout << "Ex res: " << bst.exsist(x) << "\n";
        else
            cout << "Bad cmd\n";   
    }
    return 0;
}