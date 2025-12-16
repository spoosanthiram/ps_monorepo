#pragma once

#include <Eigen/Core>

namespace Ps::Viz {

// Use Eigen Vector/Matrix for most of the basic points, vectors and colors

// Points definitions
using Point2i = Eigen::Matrix<int32_t, 2, 1>;
using Point2f = Eigen::Vector2f;
using Point2d = Eigen::Vector2d;

using Point3f = Eigen::Vector3f;
using Point3d = Eigen::Vector3d;

using Point4f = Eigen::Vector4f;

// Vectors definitions
using Vector3f = Eigen::Vector3f;
using Vector3d = Eigen::Vector3d;

// Colors definitions
using Color3f = Eigen::Vector3f;
using Color4f = Eigen::Vector4f;

} // namespace Ps::Viz
