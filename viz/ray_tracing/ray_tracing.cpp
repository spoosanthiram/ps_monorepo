#include "viz/geometry/viz_defs.h"
#include "viz/ray_tracing/ray.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <format>
#include <iostream>

Ps::Viz::Color3f ray_color(const Ps::Viz::Ray& ray)
{
    const auto alpha = 0.5 * (ray.direction().normalized().y() + 1.0);
    return (1.0 - alpha) * Ps::Viz::Color3f{1.0f, 1.0f, 1.0f} + alpha * Ps::Viz::Color3f{0.5f, 0.7f, 1.0f};
}

int main()
{
    spdlog::set_default_logger(spdlog::stderr_color_mt("err"));

    constexpr auto aspect_ratio = 16.0 / 9.0;
    constexpr auto image_width = 400;

    // Calculate the image height
    const auto image_height = static_cast<int>(image_width / aspect_ratio);
    SPDLOG_INFO("Image width: {}, height: {}", image_width, image_height);

    // Viewport
    constexpr auto viewport_height = 2.0;
    const auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
    SPDLOG_INFO("Viewport width: {}, height: {}", viewport_width, viewport_height);

    // Camera
    constexpr auto focal_length = 1.0;
    const auto camera_center = Ps::Viz::Point3d{0.0, 0.0, 0.0};

    // Horizontal & vertical viewport edges
    const auto viewport_u = Ps::Viz::Vector3d{viewport_width, 0.0, 0.0};
    const auto viewport_v = Ps::Viz::Vector3d{0.0, -viewport_height, 0.0};

    // Calculate the horizontal & vertical delta vectors from pixel to pixel
    const auto pixel_delta_u = viewport_u / image_width;
    const auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    const auto viewport_upper_left =
        camera_center - Ps::Viz::Vector3d{0.0, 0.0, focal_length} - (viewport_u / 2) - (viewport_v / 2);
    const auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    SPDLOG_INFO("pixel00_loc: ({}, {}, {})", pixel00_loc.x(), pixel00_loc.y(), pixel00_loc.z());

    std::cout << "P3\n";
    std::cout << std::format("{} {}", image_width, image_height) << '\n';
    std::cout << "255\n";

    SPDLOG_INFO("Writing PPM");
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            const auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            const auto ray_direction = pixel_center - camera_center;
            Ps::Viz::Ray ray{camera_center, ray_direction};
            const auto pixel_color = ray_color(ray);
            std::cout << std::format("{} {} {}",
                                     static_cast<int>(pixel_color.x() * 255.0),
                                     static_cast<int>(pixel_color.y() * 255.0),
                                     static_cast<int>(pixel_color.z() * 255.0))
                      << '\n';
        }
    }
    SPDLOG_INFO("Done, writing PPM");

    return 0;
}
