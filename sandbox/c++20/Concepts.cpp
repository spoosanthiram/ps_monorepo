#include <array>
#include <concepts>
#include <iostream>
#include <ranges>
#include <vector>

template <typename T>
concept Equality_comparable = requires(T x, T y) {
    { x == y };
    { x != y };
};

class MyClass
{
public:
    bool operator==(const MyClass& /*c*/) const { return true; }
    bool operator!=(const MyClass& /*c*/) const { return true; };
};

template <typename Seq, typename Num>
// requires std::ar <std::ranges::range_value_t<Seq>, Num>
Num sum(Seq seq, Num n)
{
    for (const auto x : seq) {
        n += x;
    }
    return n;
}

int main()
{
    static_assert(Equality_comparable<MyClass>);

    const auto ints = std::array{1, 2, 3, 4, 5, 6, 7};
    const auto y = sum(ints, 0);
    std::cout << std::format("sum = {}", y) << '\n';

    return 0;
}
