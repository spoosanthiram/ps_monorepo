#include "opengl_object.h"

#include "viz/geometry/gltf_reader.h"
#include "viz/geometry/model_reader.h"

#include <iostream>

namespace ps::viz {

constexpr uint32_t shader_vertex_position = 0;
constexpr uint32_t shader_vertex_normal = 1;
constexpr uint32_t shader_vertex_color = 2;

OpenGLObject::OpenGLObject(const std::filesystem::path& file_path)
{
    auto graphics_geometry = read_model(file_path);
    // init opengl buffers
    init(std::move(graphics_geometry));
}

OpenGLObject::OpenGLObject(GraphicsGeometry&& graphics_geometry)
{
    init(std::move(graphics_geometry));
}

OpenGLObject::OpenGLObject(GlTF& gltf)
{
    auto gl_funcs = OpenGLInterface::get_api();

    // Create OpenGL vertex array id and buffer ids
    gl_funcs->glGenVertexArrays(1, &vao_);
    gl_funcs->glGenBuffers(1, &position_bo_);
    gl_funcs->glGenBuffers(1, &index_bo_);

    const auto& mesh = gltf.get_meshes().front();

    // Fill OpenGL buffers and set attributes
    gl_funcs->glBindVertexArray(vao_);

    // vertex position
    const auto* position_accessor = mesh.position;
    const auto& position_buffer = position_accessor->buffer_view;
    std::cerr << "position_buffer.buff_view.size(): " << position_buffer.buff_view.size() << '\n';

    gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, position_bo_);
    gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                           position_buffer.buff_view.size() - position_accessor->byte_offset,
                           &(position_buffer.buff_view[position_accessor->byte_offset]),
                           GL_STATIC_DRAW);

    gl_funcs->glVertexAttribPointer(shader_vertex_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    gl_funcs->glEnableVertexAttribArray(shader_vertex_position);

    // vertex normal
    {
    }

    // indices
    const auto* indices_accessor = mesh.indices;
    const auto& indices_buffer = indices_accessor->buffer_view;
    std::cerr << "indices_buffer.buff_view.size(): " << indices_buffer.buff_view.size() << '\n';

    gl_funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bo_);
    gl_funcs->glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, indices_buffer.buff_view.size(), indices_buffer.buff_view.data(), GL_STATIC_DRAW);

    indices_size_ = static_cast<uint32_t>(indices_buffer.buff_view.size());
}

OpenGLObject::~OpenGLObject()
{
    // vertex array object id == 0 implies the buffers are not created, no clean up needed
    if (vao_ == 0) {
        return;
    }

    auto gl_funcs = OpenGLInterface::get_api();

    gl_funcs->glDeleteBuffers(1, &position_bo_);
    gl_funcs->glDeleteBuffers(1, &normal_bo_);
    gl_funcs->glDeleteBuffers(1, &color_bo_);
    gl_funcs->glDeleteBuffers(1, &index_bo_);

    gl_funcs->glDeleteVertexArrays(1, &vao_);
}

OpenGLObject::OpenGLObject(OpenGLObject&& other) noexcept
    : vao_{other.vao_}
    , position_bo_{other.position_bo_}
    , normal_bo_{other.normal_bo_}
    , color_bo_{other.color_bo_}
    , index_bo_{other.index_bo_}
    , indices_size_{other.indices_size_}
{
    // Reset the moved object ids to 0 so the GPU buffer doesn't get deleted twice
    other.reset_ids();
}

OpenGLObject& OpenGLObject::operator=(OpenGLObject&& other) noexcept
{
    vao_ = other.vao_;
    position_bo_ = other.position_bo_;
    normal_bo_ = other.normal_bo_;
    color_bo_ = other.color_bo_;
    index_bo_ = other.index_bo_;
    indices_size_ = other.indices_size_;

    // Reset the moved object ids to 0 so the GPU buffer doesn't get deleted twice
    other.reset_ids();

    return *this;
}

void OpenGLObject::render(const std::unique_ptr<ShaderProgram>& /*shader_program*/) const
{
    if (vao_ == 0) {
        return;
    }

    auto gl_funcs = OpenGLInterface::get_api();

    gl_funcs->glBindVertexArray(vao_);
    gl_funcs->glDrawElements(GL_TRIANGLES, indices_size_, GL_UNSIGNED_INT, nullptr);
}

void OpenGLObject::init(GraphicsGeometry&& graphics_geometry)
{
    if (graphics_geometry.vertex_positions.empty()) {
        return;
    }

    auto gl_funcs = OpenGLInterface::get_api();

    // Create OpenGL vertex array id and buffer ids
    gl_funcs->glGenVertexArrays(1, &vao_);
    gl_funcs->glGenBuffers(1, &position_bo_);
    gl_funcs->glGenBuffers(1, &normal_bo_);
    gl_funcs->glGenBuffers(1, &color_bo_);
    gl_funcs->glGenBuffers(1, &index_bo_);

    // Fill OpenGL buffers and set attributes
    gl_funcs->glBindVertexArray(vao_);

    // vertex position
    gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, position_bo_);
    gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                           graphics_geometry.vertex_positions_buffer_size(),
                           graphics_geometry.vertex_positions.data(),
                           GL_STATIC_DRAW);

    gl_funcs->glVertexAttribPointer(shader_vertex_position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    gl_funcs->glEnableVertexAttribArray(shader_vertex_position);

    // vertex normal
    gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, normal_bo_);
    gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                           graphics_geometry.vertex_normals_buffer_size(),
                           graphics_geometry.vertex_normals.data(),
                           GL_STATIC_DRAW);

    gl_funcs->glVertexAttribPointer(shader_vertex_normal, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    gl_funcs->glEnableVertexAttribArray(shader_vertex_normal);

    // vertex color
    gl_funcs->glBindBuffer(GL_ARRAY_BUFFER, color_bo_);
    gl_funcs->glBufferData(GL_ARRAY_BUFFER,
                           graphics_geometry.vertex_colors_buffer_size(),
                           graphics_geometry.vertex_colors.data(),
                           GL_STATIC_DRAW);

    gl_funcs->glVertexAttribPointer(shader_vertex_color, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
    gl_funcs->glEnableVertexAttribArray(shader_vertex_color);

    // indices
    gl_funcs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_bo_);
    gl_funcs->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                           graphics_geometry.indices_buffer_size(),
                           graphics_geometry.indices.data(),
                           GL_STATIC_DRAW);

    indices_size_ = static_cast<uint32_t>(graphics_geometry.indices.size());
}

void OpenGLObject::reset_ids()
{
    vao_ = 0;
    position_bo_ = 0;
    normal_bo_ = 0;
    color_bo_ = 0;
    index_bo_ = 0;
    indices_size_ = 0;
}

} // namespace ps::viz
