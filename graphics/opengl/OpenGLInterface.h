#pragma once

#include <QtOpenGL/QOpenGLFunctions_4_5_Core>

namespace Ps::Graphics {

constexpr int kOpenGL_Major_Version = 4;
constexpr int kOpenGL_Minor_Version = 5;

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

}  // namespace Ps::Graphics
