#include "sandbox/roblox/Int.h"

#include <format>

namespace Ps::Algo {

Int::Int(uint32_t n)
{
    bytes_.push_back(n);
}

bool Int::operator<(const Int& rhs) const
{
    if (bytes_.size() == rhs.bytes_.size()) {
        auto it = bytes_.rbegin();
        auto rhs_it = rhs.bytes_.rbegin();
        while (it != bytes_.rend() && *it == *rhs_it) {
            ++it;
            ++rhs_it;
        }
        return (it != bytes_.rend()) ? *it < *rhs_it : false;
    }

    return bytes_.size() < rhs.bytes_.size();
}

Int Int::twice() const
{
    Int x2;

    x2.bytes_ = bytes_;

    uint32_t bit_to_add = 0;
    uint32_t last_bit = 0;
    for (size_t i = 0; i < x2.bytes_.size(); ++i) {
        last_bit = x2.bytes_[i] & 0x80000000;
        x2.bytes_[i] <<= 1;
        x2.bytes_[i] += bit_to_add;
        bit_to_add = (last_bit > 0) ? 1 : 0;
    }
    if (bit_to_add > 0) {
        x2.bytes_.push_back(1);
    }

    return x2;
}

Int Int::operator+(const Int& rhs) const
{
    Int result;

    const auto max_size = std::max(bytes_.size(), rhs.bytes_.size());

    auto& result_bytes = result.bytes_;
    result_bytes.reserve(max_size + 1);

    uint64_t val = 0;
    int32_t carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        val = static_cast<uint64_t>(i < bytes_.size() ? bytes_[i] : 0) +
              static_cast<uint64_t>(i < rhs.bytes_.size() ? rhs.bytes_[i] : 0) + carry;
        result_bytes.push_back(val & 0xffffffff);
        carry = val > 0xffffffff;
    }
    if (carry > 0) {
        result_bytes.push_back(0x1);
    }

    return result;
}

std::string Int::to_hex_str() const
{
    std::string str;
    for (auto it = bytes_.rbegin(); it != bytes_.rend(); ++it) {
        std::format_to(std::back_inserter(str), "{:08x}", static_cast<uint32_t>(*it));
    }
    return str;
}

std::ostream& operator<<(std::ostream& out, const Int& x)
{
    out << x.to_hex_str();
    return out;
}

} // namespace Ps::Algo
