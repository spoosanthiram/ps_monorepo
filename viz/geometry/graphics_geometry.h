#pragma once

#include "utils/class_helper.h"
#include "viz/geometry/viz_defs.h"

#include <vector>

namespace ps::viz {

/// @brief Struct to keep the relevant geometry info that can be
///        directly used in a graphics pipeline
struct GraphicsGeometry
{
    GraphicsGeometry() = default;

    COPY_CONSTRUCTOR(GraphicsGeometry) = delete;
    COPY_ASSIGNMENT(GraphicsGeometry) = delete;

    GraphicsGeometry(GraphicsGeometry&& other) noexcept
        : vertex_positions{std::move(other.vertex_positions)}
        , vertex_normals{std::move(other.vertex_normals)}
        , vertex_colors{std::move(other.vertex_colors)}
        , indices{std::move(other.indices)}
    {}

    GraphicsGeometry& operator=(GraphicsGeometry&& other) noexcept
    {
        vertex_positions = std::move(other.vertex_positions);
        vertex_normals = std::move(other.vertex_normals);
        vertex_colors = std::move(other.vertex_colors);
        indices = std::move(other.indices);
        return *this;
    }

    size_t vertex_positions_buffer_size() const { return vertex_positions.size() * sizeof(Point3f); }
    size_t vertex_normals_buffer_size() const { return vertex_normals.size() * sizeof(Vector3f); }
    size_t vertex_colors_buffer_size() const { return vertex_colors.size() * sizeof(Point4f); }
    size_t indices_buffer_size() const { return indices.size() * sizeof(uint32_t); }

    std::vector<Point3f> vertex_positions;
    std::vector<Vector3f> vertex_normals;
    std::vector<Point4f> vertex_colors;
    std::vector<uint32_t> indices;
};

} // namespace ps::viz
