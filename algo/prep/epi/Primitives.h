#pragma once

#include <cstdint>

namespace Ps::Algo {

/// @brief EPI 5.1 Compute Parity
/// @returns true if odd number of 1 bits false otherwise
///
bool parity(uint64_t x);
bool parity_using_lookup(uint64_t x);

/// @brief EPI 5.2 Swap Bits
/// Example: swap_bits(<01001001>, 1, 6) => <00001011>
///
uint64_t swap_bits(uint64_t x, uint32_t i, uint32_t j);

/// @brief EPI 5.3 Reverse Bits
/// Example: <1010...10> => <0101...01>
///
uint64_t reverse_bits(uint64_t x);

/// @brief EPI 5.4 Closest Integer with Same Weight
///
uint64_t closest_int_with_same_bit_weight(uint64_t x);

/// @brief EPI 5.5 Multiply without * or + operators
///
uint32_t add_no_op(uint32_t x, uint32_t y);
uint32_t multiply_no_op(uint32_t x, uint32_t y);

/// @brief EPI 5.7 Compute x^y
///
double power(double x, int y);

/// @brief EPI 5.8 Reverse Digits
/// Example: 42 => 24, -314 => -413
///
int reverse(int x);

/// @brief EPI 5.9 Check if a Decimal Integer is Palindrome
/// Example: 1810181 => true, 1234 => false
///
bool is_decimal_palindrome(int x);

/// @brief EPI 5.10 Generate Uniform Random Number
///
int random(int a, int b);

/// @brief EPI 5.11 Interval Intersection test & Rectangle Intersection
///
struct Interval
{
    int32_t x1;
    int32_t x2;
};
bool is_intersect(const Interval& a, const Interval& b);

struct Rectangle
{
    bool operator==(const Rectangle& rhs) const
    {
        return x == rhs.x && y == rhs.y && width == rhs.width && height == rhs.height;
    }
    int x;
    int y;
    int width;
    int height;
};
bool is_intersect(const Rectangle& r1, const Rectangle& r2, Rectangle& result);

} // namespace Ps::Algo
