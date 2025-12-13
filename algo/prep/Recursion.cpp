#include "algo/prep/Recursion.h"

namespace Ps::Algo {

std::vector<std::string> permutations(const std::string& str)
{
    if (str.empty()) {
        return std::vector<std::string>{};
    }
    else if (str.size() == 1) {
        return std::vector<std::string>{1, str};
    }

    std::vector<std::string> words;

    std::string first_char = str.substr(0, 1);
    std::vector<std::string> word_list = permutations(str.substr(1));

    for (auto& word : word_list) {
        size_t n = word.size();
        for (size_t i = 0; i <= n; ++i) {
            words.push_back(word.substr(0, i) + first_char + word.substr(i));
        }
    }

    return words;
}

} // namespace Ps::Algo
