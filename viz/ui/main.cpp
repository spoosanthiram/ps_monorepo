#include "viz/ui/main_window.h"

#include <QtWidgets/QApplication>

#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
    try {
        QApplication app{argc, argv};

        ps::viz::MainWindow main_window;
        main_window.show();

        while (!main_window.is_closed()) {
            main_window.update_rendering();
            app.processEvents();

            std::this_thread::sleep_for(std::chrono::milliseconds{30});
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
