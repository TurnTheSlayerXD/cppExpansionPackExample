#include <iostream>

template <class... Children>
struct Div
{
    const std::tuple<Children...> &children_;
    Div(const Children &...children)
    {
        children_ = std::make_tuple(children...);
    }
};

template <int... Indices>
void help(std::ostream &stream,
          const auto &tuple,
          std::integer_sequence<int, Indices...> buf)
{
    (stream << ... << std::get<Indices>(tuple));
}

template <class... Children>
std::ostream &operator<<(std::ostream &stream,
                         const Div<Children...> &div)
{
    stream << "<div>\n\r";
    help(stream, div.children_,
         std::make_integer_sequence<int, sizeof...(Children)>{});

    stream << "</div>\n\r";
    return stream;
}

template <class Child>
struct Div<Child>
{
    const Child &child;
    Div(const Child &child) : child{child}
    {
    }
};

template <class Child>
std::ostream &operator<<(std::ostream &stream, const Div<Child> &div)
{
    stream << "<div>\n\r";
    stream << div.child;
    stream << "</div>\n\r";
    return stream;
}

template <>
struct Div<>
{
};

template <>
std::ostream &operator<<(std::ostream &stream,
                         const Div<> &div)
{
    stream << "<div>\n\r";
    stream << "</div>\n\r";
    return stream;
}
