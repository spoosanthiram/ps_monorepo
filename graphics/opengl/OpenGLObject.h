#pragma once

#include "OpenGLInterface.h"
#include "ShaderProgram.h"

#include "core/utils/ClassHelper.h"
#include "graphics/geometry/GraphicsGeometry.h"

#include <filesystem>
#include <memory>

namespace Ps::Graphics {

class GlTF;

/// @brief Class abstract the information to be used for rendering.
///        Usually initialized once and used in drawing loop
class OpenGLObject
{
public:
    OpenGLObject(const std::filesystem::path& file_path);
    OpenGLObject(GraphicsGeometry&& graphics_geometry);
    OpenGLObject(GlTF& gltf);
    ~OpenGLObject();

    COPY_CONSTRUCTOR(OpenGLObject) = delete;
    COPY_ASSIGNMENT(OpenGLObject) = delete;

    OpenGLObject(OpenGLObject&& other) noexcept;
    OpenGLObject& operator=(OpenGLObject&& other) noexcept;

    /// @brief Render the object using the shader program
    void render(const std::unique_ptr<ShaderProgram>& shader_program) const;

private:
    void init(GraphicsGeometry&& graphics_geometry);

private:
    /// @brief Vertex array & buffer object ids
    GLuint vao_{0};
    GLuint position_bo_{0};
    GLuint normal_bo_{0};
    GLuint color_bo_{0};
    GLuint index_bo_{0};
    GLuint tex_coord_bo_{0};
    GLuint texture_{0};

    /// @brief Number of indices needed to render
    uint32_t indices_size_{0};
};

}  // namespace Ps::Graphics
