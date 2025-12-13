#include "algo/other/JobSchedule.h"

#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <format>
#include <fstream>
#include <regex>

namespace Ps::Algo {

std::vector<Job> read_jobs(const std::filesystem::path& file_path)
{
    std::ifstream input_stream{file_path};
    if (!input_stream) {
        throw std::runtime_error{std::format("Could not open {} for reading jobs.", file_path.string())};
    }

    std::vector<Job> jobs;

    std::string line;
    while (!input_stream.eof() && line.empty()) {
        std::getline(input_stream, line);
    }

    int njobs = (!line.empty()) ? std::stoi(line) : 0;

    const std::regex ws_re{R"(\s+)"};

    while (!input_stream.eof() && njobs > 0) {
        std::getline(input_stream, line);
        if (line.empty()) {
            continue;
        }

        int job_weight_length[2] = {0};
        auto it = std::sregex_token_iterator{line.begin(), line.end(), ws_re, -1};
        for (int i = 0; it != std::sregex_token_iterator{}; ++i, ++it) {
            job_weight_length[i] = std::stoi(it->str());
        }
        jobs.emplace_back(job_weight_length[0], job_weight_length[1]);

        --njobs;
    }

    return jobs;
}

} // namespace Ps::Algo

TEST_CASE("AlgoClass Schedule Jobs")
{
    auto jobs = Ps::Algo::read_jobs("algo/other/test/data/AlgoClassScheduleJobs.txt");

    // Sort jobs by Difference
    std::sort(jobs.begin(), jobs.end(), [](const auto& x, const auto& y) {
        auto xval = x.weight - x.length;
        auto yval = y.weight - y.length;
        return xval == yval ? x.weight > y.weight : xval > yval;
    });
    REQUIRE(Ps::Algo::compute_weighted_completion_time(jobs) == 69'119'377'652L);

    // Sort jobs by Ratio
    std::sort(jobs.begin(), jobs.end(), [](const auto& x, const auto& y) {
        return (static_cast<double>(x.weight) / x.length) > (static_cast<double>(y.weight) / y.length);
    });
    REQUIRE(Ps::Algo::compute_weighted_completion_time(jobs) == 67'311'454'237L);
}
