#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Ps::Algo {

/// @brief Integer as bit stream
/// Represent interger as vector<uint32_t>. LSB at 0th position and MSB at size - 1
/// Only mutiple by 2 and addition supported
/// x * 2 is computed as x << 1
/// x * 3 is computed as (x * 2) + x
/// x * 5 is computed as (x * 2) + (x * 3)
/// Please the algorithm below
/// operators == & < are used to StrInt in std::set
class Int
{
public:
    Int() = default;
    explicit Int(uint32_t n);

    bool operator==(const Int& rhs) const { return bytes_ == rhs.bytes_; }
    bool operator<(const Int& rhs) const;

    Int twice() const;
    Int operator+(const Int& rhs) const;

    std::string to_hex_str() const;

private:
    std::vector<uint32_t> bytes_;
};

std::ostream& operator<<(std::ostream& out, const Int& x);

} // namespace Ps::Algo
