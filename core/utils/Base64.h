#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace Ps::Core {

int32_t base64_char_to_value(char ch);

std::vector<unsigned char> base64_decode(std::string_view base64_str);

}  // namespace Ps::Core
