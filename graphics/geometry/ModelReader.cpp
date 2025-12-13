#include "ModelReader.h"

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <regex>

namespace fs = std::filesystem;

namespace Ps::Graphics {

GraphicsGeometry read_bin(const fs::path& file_path)
{
    std::ifstream bin_stream{file_path, std::ios::binary};
    if (!bin_stream) {
        throw std::runtime_error{fmt::format("Could not open {}", file_path.string())};
    }

    // number of vertices
    uint32_t num_vertices = 0;
    bin_stream.read(reinterpret_cast<char*>(&num_vertices), sizeof(num_vertices));

    GraphicsGeometry graphics_geometry;

    // vertices
    {
        graphics_geometry.vertex_positions.reserve(num_vertices);
        graphics_geometry.vertex_normals.reserve(num_vertices);
        graphics_geometry.vertex_colors.reserve(num_vertices);

        Point3f pos;
        Vector3f normal;
        Point4f color;
        for (uint32_t i = 0; i < num_vertices; ++i) {
            bin_stream.read(reinterpret_cast<char*>(pos.data()), sizeof(pos));
            bin_stream.read(reinterpret_cast<char*>(normal.data()), sizeof(normal));
            bin_stream.read(reinterpret_cast<char*>(color.data()), sizeof(color));

            graphics_geometry.vertex_positions.push_back(pos);
            graphics_geometry.vertex_normals.push_back(normal);
            graphics_geometry.vertex_colors.push_back(color);
        }
    }

    // number of triangles
    uint32_t num_triangles = 0;
    bin_stream.read(reinterpret_cast<char*>(&num_triangles), sizeof(num_triangles));

    // indices
    {
        graphics_geometry.indices.reserve(num_triangles * 3);

        uint32_t val = 0;
        for (uint32_t i = 0; i < num_triangles; ++i) {
            for (int j = 0; j < 3; ++j) {
                bin_stream.read(reinterpret_cast<char*>(&val), sizeof(val));
                graphics_geometry.indices.push_back(val);
            }
        }
    }

    return graphics_geometry;
}

GraphicsGeometry read_obj(const fs::path& file_path)
{
    std::ifstream obj_stream{file_path};
    if (!obj_stream) {
        throw std::runtime_error{fmt::format("Could not open {}", file_path.string())};
    }

    GraphicsGeometry graphics_geometry;

    auto ws_pattern = std::regex{R"(\s+)"};

    std::string line;
    while (!obj_stream.eof()) {
        std::getline(obj_stream, line);
        if (line.empty() || line[0] == '#' || line[0] == 'g') {
            continue;
        }

        const std::sregex_token_iterator end_it;
        auto it = std::sregex_token_iterator{line.begin(), line.end(), ws_pattern, -1};
        const auto desig = it->str();

        if (desig == "v") {
            Point3f pos;
            auto i = 0;
            for (++it; it != end_it; ++it) {
                pos[i++] = std::stof(it->str());
            }
            graphics_geometry.vertex_positions.push_back(pos);
        }
        else if (desig == "vn") {
            Vector3f normal;
            auto i = 0;
            for (++it; it != end_it; ++it) {
                normal[i++] = std::stof(it->str());
            }
            normal.normalize();
            graphics_geometry.vertex_normals.push_back(normal);
        }
        else if (desig == "vt") {
            Point4f color{0.4f, 0.6f, 0.6f, 1.0f};
            graphics_geometry.vertex_colors.push_back(color);
        }
        else if (desig == "f") {
            auto face_pattern = std::regex{R"((\d+)/(\d*)/(\d*))"};
            for (++it; it != end_it; ++it) {
                std::string face = it->str();
                std::smatch matches;
                if (std::regex_match(face, matches, face_pattern)) {
                    // first one is vertex index
                    std::ssub_match vertex_index_match = matches[1];
                    graphics_geometry.indices.push_back(static_cast<uint32_t>(std::stoi(vertex_index_match.str()) - 1));

                    // second one is texture index, ignore for now!
                    // third one is normal index, ignore for now!
                }
            }
        }
    }

    return graphics_geometry;
}

GraphicsGeometry read_model(const fs::path& file_path)
{
    if (file_path.extension() == ".bin") {
        return read_bin(file_path);
    }
    else if (file_path.extension() == ".obj") {
        return read_obj(file_path);
    }
    SPDLOG_ERROR(fmt::format("Model file {} is not supported yet!", file_path.string()));
    return GraphicsGeometry{};
}

}  // namespace Ps::Graphics
