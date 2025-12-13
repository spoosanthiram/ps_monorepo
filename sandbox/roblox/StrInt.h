#pragma once

#include <cstdint>
#include <string>

namespace Ps::Algo {

/// @brief StrInt - Interger as string
/// Represents 230 as {'0', '3', '2'} - most significant digit added to end of the string
/// Easy to debug & print. Fairly fast up until < 1,000,000th position
/// Since the algorithm (see multiples.cpp), needs only multiplcation by 2, 3 and 5
/// only supports multiplication by a single digit number.
/// operators == & < are used to keep StrInt in std::set
class StrInt
{
public:
    StrInt() = default;
    explicit StrInt(uint32_t n);

    bool operator==(const StrInt& rhs) const { return str_int_ == rhs.str_int_; }
    bool operator<(const StrInt& rhs) const;

    StrInt operator*(int n) const;

    std::string to_decimal_string() const;

private:
    std::string str_int_;
};

std::ostream& operator<<(std::ostream& out, const StrInt& str_int);

} // namespace Ps::Algo
