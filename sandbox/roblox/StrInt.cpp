#include "sandbox/roblox/StrInt.h"

#include <algorithm>
#include <stdexcept>

namespace Ps::Algo {

StrInt::StrInt(uint32_t n)
{
    if (n == 0) {
        str_int_.push_back('0');
        return;
    }

    while (n > 0) {
        str_int_.push_back(static_cast<char>(n % 10 + '0'));
        n /= 10;
    }
}

bool StrInt::operator<(const StrInt& rhs) const
{
    if (str_int_.size() == rhs.str_int_.size()) {
        auto it = str_int_.rbegin();
        auto rhs_it = rhs.str_int_.rbegin();
        while (it != str_int_.rend() && *it == *rhs_it) {
            ++it;
            ++rhs_it;
        }
        return (it != str_int_.rend()) ? *it < *rhs_it : false;
    }

    return str_int_.size() < rhs.str_int_.size();
}

StrInt StrInt::operator*(int n) const
{
    if (n > 9) {
        throw std::logic_error{"Single digit multiplier only"};
    }

    StrInt result;
    auto& result_str = result.str_int_;
    result_str.reserve(str_int_.size() + 1);

    int val = 0;
    int carry = 0;
    for (auto ch : str_int_) {
        val = (ch - '0') * n + carry;
        result_str.push_back(static_cast<char>(val % 10 + '0'));
        carry = val / 10;
    }
    if (carry > 0) {
        result_str.push_back(static_cast<char>(carry + '0'));
    }

    return result;
}

std::string StrInt::to_decimal_string() const
{
    std::string decimal_str;
    int i = 0;
    for (const auto ch : str_int_) {
        if (i != 0 && i % 3 == 0) {
            decimal_str.push_back(',');
        }
        decimal_str.push_back(ch);
        ++i;
    }
    std::reverse(decimal_str.begin(), decimal_str.end());
    return decimal_str;
}

std::ostream& operator<<(std::ostream& out, const StrInt& str_int)
{
    out << str_int.to_decimal_string();
    return out;
}

} // namespace Ps::Algo
