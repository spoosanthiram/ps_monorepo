#include "MainWindow.h"

namespace Ps::Graphics {

constexpr int kInitial_Width = 1300;
constexpr int kInitial_Height = 900;

MainWindow::MainWindow()
{
    setWindowTitle("Viewer");
    setGeometry(0, 0, kInitial_Width, kInitial_Height);

    gl_view_ = new OpenGLWidget{this};
    setCentralWidget(gl_view_);
}

void MainWindow::update_rendering()
{
    gl_view_->update();
}

void MainWindow::closeEvent(QCloseEvent* /*close_event*/)
{
    window_closed_ = true;
}

}  // namespace Ps::Graphics
