#pragma once

#include "viz/geometry/graphics_geometry.h"

#include <filesystem>

namespace ps::viz {

GraphicsGeometry read_model(const std::filesystem::path& file_path);

} // namespace ps::viz
