#include "core/utils/Utils.h"

#include <exception>
#include <format>

namespace Ps::Core {

std::ifstream open_stream(const std::filesystem::path& file_path)
{
    std::ifstream input_stream{file_path};
    if (!input_stream) {
        throw std::runtime_error{std::format("Could not open {} file.", file_path.string())};
    }
    return input_stream;
}

std::vector<int> read_integers(const std::filesystem::path& file_path)
{
    auto input_stream = open_stream(file_path);

    std::vector<int> integers;

    std::string line;
    while (!input_stream.eof()) {
        std::getline(input_stream, line);
        if (line.size() > 0)
            integers.push_back(std::stoi(line));
    }

    return integers;
}

}  // namespace Ps::Core
