#include <cassert>
#include <variant>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <optional>
#include <tuple>
#include <array>
#include <format>

template <class... T>
auto sum_all(T... args)
{
    return (0 + ... + args);
}

template <class T>
struct AddSpace
{
    const T &ref;
    AddSpace(const T &ref) : ref{ref} {}
};

template <class T>
std::ostream &operator<<(std::ostream &str, AddSpace<T> arg)
{
    str << arg.ref << "_";
    return str;
}

template <class... T>
void print_all(T... args)
{
    (std::cout << ... << AddSpace{args}) << "\r\n";
}

#include <iostream>
template <class T>
struct Node
{
    T data;
    Node *left;
    Node *right;
    Node(T data) : data{data}, left{nullptr}, right{nullptr}
    {
    }
};
template <class T, class U>
Node<T> &operator+(const Node<T> &t, U ptr)
{
    return *(t.*ptr);
}
template <class T, class... U>
Node<T> *tree_get(Node<T> *top, U... args)
{
    return &(*top + ... + args);
}

template <class T>
void clean_tree(Node<T> *v)
{
    if (v == nullptr)
    {
        return;
    }
    clean_tree(v->left);
    clean_tree(v->right);
    delete v;
}

template <class T, class... U>
void print_spaced(std::ostream &stream, const T &first, const U &...args)
{
    if constexpr (sizeof...(args) == 0)
    {
        stream << first << "\n\r";
    }
    else
    {
        stream << first << " ";
        print_spaced(stream, args...);
    }
}

template <typename T>
int foo() { return 1; }
template <>
int foo<int>() { return 2; }
template <>
int foo<float>() { return 4; }
template <typename... T>
int sumfoos() { return (foo<T>() + ...); }

template <class T>
struct S
{
    static auto fun()
    {
        return 0;
    }
};
template <class... Rest>
struct S<std::tuple<Rest...>>
{
    static auto fun()
    {
        return sumfoos<Rest...>();
    }
};

template <class Tuple>
int apply_sumfoos()
{

    return S<Tuple>::fun();
}



int main()
{


    std::tuple<int, float, double> t;
    assert(apply_sumfoos<decltype(t)>() == 7);

#if 0
    constexpr auto left = &Node<int>::left;
    constexpr auto right = &Node<int>::right;
    Node<int> *top = new Node<int>(1);
    top->left = new Node<int>(2);
    top->left->left = new Node<int>(3);
    top->left->left->right = new Node<int>(4);
    auto target = tree_get(top, left, left, right);
    std::cout << "data: " << target->data;
    clean_tree(top);
#endif
    return 0;
}
