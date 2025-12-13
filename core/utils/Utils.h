#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

namespace Ps::Core {

/**
 * Open stream from the file path given
 * Throws runtime_error
 */
std::ifstream open_stream(const std::filesystem::path& file_path);

/**
 * Read integers from file
 * One integer per line
 */
std::vector<int> read_integers(const std::filesystem::path& file_path);

}  // namespace Ps::Core
