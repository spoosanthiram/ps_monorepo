#include "main_window.h"

namespace ps::viz {

constexpr int initial_width = 1300;
constexpr int initial_height = 900;

MainWindow::MainWindow()
{
    setWindowTitle("Viewer");
    setGeometry(0, 0, initial_width, initial_height);

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

} // namespace ps::viz
