#include "algo/other/Knapsack.h"

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <fstream>
#include <regex>

namespace Ps::Algo {

std::pair<unsigned int, std::vector<KnapsackItem>> read_knapsack_items(const std::filesystem::path& file_path)
{
    auto pattern = std::regex{R"(\s+)"};

    std::ifstream stream{file_path};
    if (!stream) {
        throw std::runtime_error{std::format("Could not open {} for reading knapsack items.", file_path.string())};
    }

    std::string buf;

    // read knapsack size & items
    std::getline(stream, buf);
    auto it = std::sregex_token_iterator{buf.begin(), buf.end(), pattern, -1};
    unsigned int W = std::stoi(it->str());
    size_t n = std::stoi((++it)->str());

    std::vector<KnapsackItem> items;
    items.reserve(n);

    while (!stream.eof()) {
        std::getline(stream, buf);
        if (buf.empty()) {
            continue;
        }

        auto it = std::sregex_token_iterator{buf.begin(), buf.end(), pattern, -1};
        int value = std::stoi(it->str());
        int weight = std::stoi((++it)->str());

        items.emplace_back(value, weight);
    }

    return std::make_pair(W, std::move(items));
}

} // namespace Ps::Algo

TEST_CASE("AlgoClass Knapsack")
{
    auto retval = Ps::Algo::read_knapsack_items("algo/other/test/data/AlgoClassKnapsack.txt");
    REQUIRE(Ps::Algo::knapsack(retval.second, retval.first) == 2'493'893);
}

TEST_CASE("AlgoClass Knapsack Big")
{
    auto retval = Ps::Algo::read_knapsack_items("algo/other/test/data/AlgoClassKnapsackBig.txt");
    REQUIRE(Ps::Algo::knapsack(retval.second, retval.first) == 4'243'395);
}
