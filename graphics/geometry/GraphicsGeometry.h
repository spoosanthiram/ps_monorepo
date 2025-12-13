#pragma once

#include "core/utils/ClassHelper.h"

#include <Eigen/Core>

#include <vector>

namespace Ps::Graphics {

using Point2i = Eigen::Matrix<int32_t, 2, 1>;
using Point2f = Eigen::Vector2f;
using Point2d = Eigen::Vector2d;

using Point3f = Eigen::Vector3f;
using Point3d = Eigen::Vector3d;

using Vector3f = Eigen::Vector3f;
using Vector3d = Eigen::Vector3d;

using Point4f = Eigen::Vector4f;

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
        , texture_coords{std::move(other.texture_coords)}
        , indices{std::move(other.indices)}
    {}

    GraphicsGeometry& operator=(GraphicsGeometry&& other) noexcept
    {
        vertex_positions = std::move(other.vertex_positions);
        vertex_normals = std::move(other.vertex_normals);
        vertex_colors = std::move(other.vertex_colors);
        texture_coords = std::move(other.texture_coords);
        indices = std::move(other.indices);
        return *this;
    }

    size_t vertex_positions_buffer_size() const { return vertex_positions.size() * sizeof(Point3f); }
    size_t vertex_normals_buffer_size() const { return vertex_normals.size() * sizeof(Vector3f); }
    size_t vertex_colors_buffer_size() const { return vertex_colors.size() * sizeof(Point4f); }
    size_t texture_coords_buffer_size() const { return texture_coords.size() * sizeof(Point2f); }
    size_t indices_buffer_size() const { return indices.size() * sizeof(uint32_t); }

    std::vector<Point3f> vertex_positions;
    std::vector<Vector3f> vertex_normals;
    std::vector<Point4f> vertex_colors;
    std::vector<Point2f> texture_coords;
    std::vector<uint32_t> indices;
};

}  // namespace Ps::Graphics
