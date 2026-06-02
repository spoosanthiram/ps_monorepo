#pragma once

#include <QtOpenGL/QOpenGLFunctions_4_5_Core>

namespace ps::viz {

constexpr int opengl_major_version = 4;
constexpr int opengl_minor_version = 5;

class OpenGLInterface
{
public:
    using OpenGLFunctions = QOpenGLFunctions_4_5_Core;

public:
    OpenGLInterface() = delete;

    static OpenGLFunctions* get_api();
    static void set_api(OpenGLFunctions* funcs);

private:
    static OpenGLFunctions* gl_funcs_;
};

} // namespace ps::viz
