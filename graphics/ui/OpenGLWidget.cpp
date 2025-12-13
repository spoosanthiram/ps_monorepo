#include "OpenGLWidget.h"

#include "graphics/geometry/gltf_reader.h"
#include "graphics/opengl/OpenGLObject.h"
#include "graphics/opengl/ShaderProgram.h"

#include <QtGui/QMouseEvent>
#include <QtOpenGL/QOpenGLVersionFunctionsFactory>
#include <spdlog/spdlog.h>

#include <iostream>
#include <numbers>

namespace Ps::Graphics {

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget{parent}
{
    constexpr auto kNumber_Of_Sample = 4;

    setFocusPolicy(Qt::StrongFocus);

    QSurfaceFormat format = QOpenGLWidget::format();
    format.setVersion(kOpenGL_Major_Version, kOpenGL_Minor_Version);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSamples(kNumber_Of_Sample);
    setFormat(format);
}

OpenGLWidget::~OpenGLWidget() = default;

void OpenGLWidget::initializeGL()
{
    OpenGLInterface::OpenGLFunctions* funcs =
        QOpenGLVersionFunctionsFactory::get<OpenGLInterface::OpenGLFunctions>(context());
    if (!funcs) {
        throw std::runtime_error("Resolving Open GL functions failed.");
    }
    OpenGLInterface::set_api(funcs);

    auto gl_funcs = OpenGLInterface::get_api();

    SPDLOG_INFO("GL_VENDOR: {}", reinterpret_cast<const char*>(gl_funcs->glGetString(GL_VENDOR)));
    SPDLOG_INFO("GL_RENDERER: {}", reinterpret_cast<const char*>(gl_funcs->glGetString(GL_RENDERER)));
    SPDLOG_INFO("GL_VERSION: {}", reinterpret_cast<const char*>(gl_funcs->glGetString(GL_VERSION)));
    SPDLOG_INFO("GL_SHADING_LANGUAGE_VERSION: {}",
                reinterpret_cast<const char*>(gl_funcs->glGetString(GL_SHADING_LANGUAGE_VERSION)));

    gl_funcs->glEnable(GL_MULTISAMPLE);

    gl_funcs->glEnable(GL_DEPTH_TEST);
    gl_funcs->glDepthFunc(GL_LEQUAL);

    gl_funcs->glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

    load_shaders();

    // opengl_object_ = std::make_unique<OpenGLObject>("graphics/data/models/model.bin");

    // create Geometry
    // {
    //     GraphicsGeometry geom;

    //     geom.vertex_positions.push_back({-0.5f, -0.5f, -2.5f});  // bottom left
    //     geom.vertex_positions.push_back({0.5f, -0.5f, -2.5f});   // bottom right
    //     geom.vertex_positions.push_back({0.5f, 0.5f, -2.5f});    // top right
    //     geom.vertex_positions.push_back({-0.5f, 0.5f, -2.5f});   // top lef

    //     geom.vertex_colors.push_back({1.0f, 0.0f, 0.0f, 1.0f});  // bottom left color
    //     geom.vertex_colors.push_back({0.0f, 1.0f, 0.0f, 1.0f});  // bottom right color
    //     geom.vertex_colors.push_back({0.0f, 0.0f, 1.0f, 1.0f});  // top right color
    //     geom.vertex_colors.push_back({1.0f, 1.0f, 0.0f, 1.0f});  // top lef color

    //     geom.texture_coords.push_back({0.0f, 0.0f});
    //     geom.texture_coords.push_back({1.0f, 0.0f});
    //     geom.texture_coords.push_back({1.0f, 1.0f});
    //     geom.texture_coords.push_back({0.0f, 1.0f});

    //     // triangle 1
    //     geom.indices.push_back(0);
    //     geom.indices.push_back(1);
    //     geom.indices.push_back(2);

    //     // triangle 2
    //     geom.indices.push_back(0);
    //     geom.indices.push_back(2);
    //     geom.indices.push_back(3);

    //     opengl_object_ = std::make_unique<OpenGLObject>(std::move(geom));
    // }

    GlTF gltf{"graphics/data/models/box/gltf-embedded/box.gltf"};
    opengl_object_ = std::make_unique<OpenGLObject>(gltf);
}

void OpenGLWidget::resizeGL(int width, int height)
{
    if (width_ == width && height_ == height) {
        return;
    }

    width_ = width;
    height_ = height;

    constexpr double FOVY = 45.0;
    constexpr double NEAR = 1.0;
    constexpr double FAR = 100.0;

    double aspect_ratio = static_cast<double>(width_) / static_cast<double>(height_);

    projection_matrix_.setZero();

    double q = 1.0 / std::tan(0.5 * FOVY * std::numbers::pi / 180.0);
    projection_matrix_(0, 0) = q / aspect_ratio;
    projection_matrix_(1, 1) = q;
    projection_matrix_(2, 2) = (NEAR + FAR) / (NEAR - FAR);
    projection_matrix_(2, 3) = -1.0;
    projection_matrix_(3, 2) = (2.0 * NEAR * FAR) / (NEAR - FAR);

    OpenGLInterface::get_api()->glViewport(0, 0, width_, height_);
}

void OpenGLWidget::paintGL()
{
    auto gl_funcs = OpenGLInterface::get_api();

    gl_funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_program_->use();
    shader_program_->set_matrix("projection_matrix", projection_matrix_);
    shader_program_->set_matrix("model_view_matrix", viewpoint_camera_.get_view_matrix());
    opengl_object_->render(shader_program_);
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* mouse_event)
{
    Point2i mouse_position{mouse_event->position().x(), mouse_event->position().y()};

    const auto start_pos = normalize(previous_mouse_position_);
    const auto end_pos = normalize(mouse_position);

    viewpoint_camera_.rotate(start_pos, end_pos);

    previous_mouse_position_ = mouse_position;
}

void OpenGLWidget::mousePressEvent(QMouseEvent* mouse_event)
{
    previous_mouse_position_ = Point2i{mouse_event->position().x(), mouse_event->position().y()};
}

void OpenGLWidget::wheelEvent(QWheelEvent* wheel_event)
{
    viewpoint_camera_.zoom(wheel_event->angleDelta().y() / 100);
}

void OpenGLWidget::load_shaders()
{
    shader_program_ = std::unique_ptr<ShaderProgram>{new ShaderProgram{}};

    Shader vertex_shader{GL_VERTEX_SHADER};
    vertex_shader.compile("graphics/shaders/simple.vert");
    shader_program_->attach_shader(std::move(vertex_shader));

    Shader fragement_shader{GL_FRAGMENT_SHADER};
    fragement_shader.compile("graphics/shaders/simple.frag");
    shader_program_->attach_shader(std::move(fragement_shader));

    shader_program_->link();
}

Point2d OpenGLWidget::normalize(const Point2i& position)
{
    return Point2d{(2.0 * position.x() - width_) / static_cast<double>(width_),
                   (height_ - 2.0 * position.y()) / static_cast<double>(height_)};
}

}  // namespace Ps::Graphics
