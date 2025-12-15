#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <format>
#include <iostream>

int main()
{
    spdlog::set_default_logger(spdlog::stderr_color_mt("err"));

    int image_width = 400;
    int image_height = 300;
    std::cout << "P3\n";
    std::cout << std::format("{} {}", image_width, image_height) << '\n';
    std::cout << "255\n";

    SPDLOG_INFO("Writing PPM");
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = static_cast<double>(i) / (image_width - 1);
            auto g = static_cast<double>(j) / (image_height - 1);
            auto b = 0.0;
            std::cout << std::format("{} {} {}",
                                     static_cast<int>(255.99 * r),
                                     static_cast<int>(255.99 * g),
                                     static_cast<int>(255.99 * b))
                      << '\n';
        }
    }
    SPDLOG_INFO("Done, writing PPM");

    return 0;
}
