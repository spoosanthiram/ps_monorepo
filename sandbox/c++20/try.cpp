#include <chrono>
#include <iostream>
#include <regex>
#include <string>

int main()
{
    auto t = std::chrono::system_clock::now();
    std::cout << "Current time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count()
              << " ms since epoch\n";

    std::time_t newt = std::chrono::system_clock::to_time_t(t);
    std::cout << "Current time: " << newt << " seconds since epoch\n";

    return 0;

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
