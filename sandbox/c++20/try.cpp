#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::regex pattern{R"(,\s+)"};
    std::string line;
    while (std::getline(std::cin, line)) {
        auto it = std::sregex_token_iterator{line.begin(), line.end(), pattern, -1};
        const std::sregex_token_iterator end_it;
        for (; it != end_it; ++it) {
            std::cout << it->str() << '\n';
        }
    }

    return 0;
}
