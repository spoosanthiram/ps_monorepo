#include "Shader.h"

#include <fmt/format.h>

#include <fstream>

namespace Ps::Graphics {

Shader::Shader(GLenum shader_type)
    : shader_type_{shader_type}
{
    shader_id_ = OpenGLInterface::get_api()->glCreateShader(shader_type_);
    if (shader_id_ == 0) {
        throw std::runtime_error{fmt::format("Could not create {}", get_type_str())};
    }
}

Shader::~Shader()
{
    if (shader_id_ != 0) {
        OpenGLInterface::get_api()->glDeleteShader(shader_id_);
    }
}

std::string_view Shader::get_type_str() const
{
    switch (shader_type_) {
        case GL_VERTEX_SHADER:
            return "Vertex Shader";
        case GL_FRAGMENT_SHADER:
            return "Fragment Shader";
        default:
            return "Unknown Shader";
    }
}

void Shader::compile(const std::filesystem::path& file_path)
{
    auto gl_api = OpenGLInterface::get_api();

    std::ifstream input_stream{file_path.c_str()};
    if (!input_stream) {
        throw std::runtime_error{fmt::format("Could not open '{}' shader file", file_path.string())};
    }
    std::string file_content{std::istreambuf_iterator<char>{input_stream}, std::istreambuf_iterator<char>{}};

    auto source = file_content.c_str();
    gl_api->glShaderSource(shader_id_, 1, &source, nullptr);

    gl_api->glCompileShader(shader_id_);

    GLint is_compiled;
    gl_api->glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        constexpr auto kLog_Length = 1024;
        GLsizei log_lenth;
        char log[kLog_Length];
        gl_api->glGetShaderInfoLog(shader_id_, kLog_Length, &log_lenth, static_cast<char*>(log));
        throw std::runtime_error{fmt::format("{} compilation failed. Error: {}", get_type_str(), log)};
    }
}

}  // namespace Ps::Graphics
