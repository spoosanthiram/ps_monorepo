#pragma once

#include "GraphicsGeometry.h"

#include <filesystem>

namespace Ps::Graphics {

GraphicsGeometry read_model(const std::filesystem::path& file_path);

}  // namespace Ps::Graphics
