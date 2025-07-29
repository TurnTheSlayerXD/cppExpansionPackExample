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

struct foo
{
    int a_;
    foo(int a) : a_{a}
    {
    }

    auto operator()()
    {
        return [this]()
        {
            a_++;
            std::cout << a_ << "\n";
        };
    }
};

int main()
{
    auto x = foo(1)();
    x();
    x();

    auto y = foo(2)();
    y();
    y();

    return 0;
}
