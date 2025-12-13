#pragma once

#include "core/utils/ClassHelper.h"
#include "graphics/geometry/GraphicsGeometry.h"
#include "graphics/geometry/ViewpointCamera.h"

#include <Eigen/Core>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include <memory>
#include <vector>

namespace Ps::Graphics {

class OpenGLObject;
class ShaderProgram;

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget(QWidget* parent);
    ~OpenGLWidget() override;

    COPY_CONSTRUCTOR(OpenGLWidget) = delete;
    MOVE_CONSTRUCTOR(OpenGLWidget) = delete;

    COPY_ASSIGNMENT(OpenGLWidget) = delete;
    MOVE_ASSIGNMENT(OpenGLWidget) = delete;

protected:
    /// @brief Overrides of QOpenGLWidget
    /// @{
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent* mouse_event) override;
    void mousePressEvent(QMouseEvent* mouse_event) override;
    void wheelEvent(QWheelEvent* wheel_event) override;
    /// @}

private:
    void load_shaders();
    Point2d normalize(const Point2i& position);

private:
    int32_t width_{0};
    int32_t height_{0};

    std::unique_ptr<ShaderProgram> shader_program_;
    Eigen::Matrix4d projection_matrix_;
    ViewpointCamera viewpoint_camera_;

    std::unique_ptr<OpenGLObject> opengl_object_;

    Point2i previous_mouse_position_{0, 0};
};

}  // namespace Ps::Graphics
