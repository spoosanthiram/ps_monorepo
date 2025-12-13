#include "Primitives.h"

#include <random>
#include <stdexcept>

namespace Ps::Algo {

constexpr auto kFourBitParityLookup = 0b0110100110010110;
constexpr uint32_t k4BitsReverseLookup[16] = {0b0000,
                                              0b1000,
                                              0b0100,
                                              0b1100,
                                              0b0010,
                                              0b1010,
                                              0b0110,
                                              0b1110,
                                              0b0001,
                                              0b1001,
                                              0b0101,
                                              0b1101,
                                              0b0011,
                                              0b1011,
                                              0b0111,
                                              0b1111};

bool parity(uint64_t x)
{
    int result = 0;
    while (x) {
        result ^= 1;
        x &= (x - 1); // clear lowest 1 bit
    }
    return result > 0;
}

bool parity_using_lookup(uint64_t x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;

    x = x & 0xf;

    return (kFourBitParityLookup >> x) & 1;
}

uint64_t swap_bits(uint64_t x, uint32_t i, uint32_t j)
{
    if (((x >> i) & 1) != ((x >> j) & 1)) {
        const auto bit_mask = (static_cast<uint64_t>(1) << i) | (static_cast<uint64_t>(1) << j);
        x ^= bit_mask;
    }
    return x;
}

uint64_t reverse_bits(uint64_t x)
{
    uint64_t y = 0;
    const auto len = static_cast<int>(sizeof(uint64_t) * 2); // 4 bit lookup, so number of bytes * 2
    for (int i = 0; i < len; ++i) {
        y <<= 4;
        y |= k4BitsReverseLookup[x & 0xf];
        x >>= 4;
    }
    return y;
}

uint64_t closest_int_with_same_bit_weight(uint64_t x)
{
    int len = sizeof(uint64_t) * 8 - 1;
    for (int i = 0; i < len; ++i) {
        if (((x >> i) & 1) != ((x >> (i + 1)) & 1))
            return x ^ ((static_cast<uint64_t>(1) << i) | (static_cast<uint64_t>(1) << (i + 1)));
    }
    throw std::invalid_argument("All bits are either 0 or 1");
}

uint32_t add_no_op(uint32_t x, uint32_t y)
{
    uint32_t result = 0;

    uint32_t carry = 0;
    uint32_t k = 0;
    uint32_t a, b;
    for (; x || y; ++k) {
        a = x & 1;
        b = y & 1;
        result |= (carry ^ a ^ b) << k;
        carry = (a & b) | (b & carry) | (a & carry);
        x >>= 1;
        y >>= 1;
    }
    result |= carry << k;

    return result;
}

uint32_t multiply_no_op(uint32_t x, uint32_t y)
{
    uint32_t result = 0;
    while (y) {
        if (y & 1) {
            result = add_no_op(result, x);
        }
        x <<= 1;
        y >>= 1;
    }
    return result;
}

double power(double x, int y)
{
    if (y < 0) {
        y = -y;
        x = 1.0 / x;
    }

    double result = 1.0;

    while (y) {
        if (y & 1) {
            result *= x;
        }
        x *= x;
        y >>= 1;
    }

    return result;
}

int reverse(int x)
{
    bool is_negative = false;
    if (x < 0) {
        is_negative = true;
        x = -x;
    }

    int y = 0;

    while (x) {
        y = y * 10 + x % 10;
        x /= 10;
    }

    return is_negative ? -y : y;
}

bool is_decimal_palindrome(int x)
{
    if (x < 0) {
        return false;
    }
    return x == reverse(x);
}

int bits_needed(int x)
{
    int nbits = 0;
    while (x) {
        ++nbits;
        x >>= 1;
    }
    return nbits;
}

int random(int a, int b)
{
    int result = 0;

    static std::default_random_engine re{};                 // static so that it is seeded once
    std::uniform_int_distribution<int> zero_one_dist{0, 1}; // for coin toss (0, 1) random value

    int nbits = bits_needed(b - a);

    while (true) {
        result = 0;
        for (int i = 0; i < nbits; ++i) {
            result = (result << 1) | zero_one_dist(re);
        }
        if (result <= (b - a)) {
            break;
        }
    }

    return result + a;
}

bool is_intersect(const Interval& a, const Interval& b)
{
    return (a.x1 <= b.x2) && (b.x1 <= a.x2);
}

bool is_intersect(const Rectangle& r1, const Rectangle& r2, Rectangle& result)
{
    int xmin = std::max(r1.x, r2.x);
    int xmax = std::min(r1.x + r1.width, r2.x + r2.width);
    if (xmin > xmax) {
        return false;
    }

    int ymin = std::max(r1.y, r2.y);
    int ymax = std::min(r1.y + r1.height, r2.y + r2.height);
    if (ymin > ymax) {
        return false;
    }

    result = Rectangle{xmin, ymin, xmax - xmin, ymax - ymin};
    return true;
}

} // namespace Ps::Algo
