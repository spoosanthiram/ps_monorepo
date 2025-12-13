#pragma once

#include "Shader.h"

#include "core/utils/ClassHelper.h"
#include "graphics/geometry/GraphicsGeometry.h"

namespace Ps::Graphics {

/// @brief Class for OpenGL shader program
class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    COPY_CONSTRUCTOR(ShaderProgram) = delete;
    MOVE_CONSTRUCTOR(ShaderProgram) = delete;
    COPY_ASSIGNMENT(ShaderProgram) = delete;
    MOVE_ASSIGNMENT(ShaderProgram) = delete;

    /// @brief Attach vertex or fragement shader
    void attach_shader(Shader&& shader);

    /// @brief link the compiled shaders.
    void link() const;

    /// @brief Set the GLSL uniform matrix 4x4 value
    void set_matrix(const std::string& name, const Eigen::Matrix4d& matrix);

    void set_color(const std::string& name, const Point4f& color);

    // @brief Use the shader program
    void use() const;

private:
    /// @brief Look up GLSL uniform location id in the stored map.
    ///        Get uniform location id and add to map if look up fails
    GLint lookup_location(const std::string& name);

private:
    GLuint program_id_{0};
    std::vector<Shader> shaders_;
    std::unordered_map<std::string, GLint> location_map_;
};

}  // namespace Ps::Graphics
