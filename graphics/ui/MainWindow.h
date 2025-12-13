#pragma once

#include "OpenGLWidget.h"

#include <QtCore/QPointer>
#include <QtWidgets/QMainWindow>

namespace Ps::Graphics {

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    ~MainWindow() override = default;

    bool is_closed() const { return window_closed_; }
    void update_rendering();

protected:
    void closeEvent(QCloseEvent* close_event) override;

private:
    QPointer<OpenGLWidget> gl_view_;
    bool window_closed_{false};
};

}  // namespace Ps::Graphics
