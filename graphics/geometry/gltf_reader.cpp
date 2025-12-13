#include "gltf_reader.h"

#include "core/utils/base64.h"

#include <draco/point_cloud/point_cloud.h>
#include <Eigen/Core>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#ifdef __llvm__
  #include <fmt/format.h>
#else
  #include <format>
#endif
#include <fstream>
#include <iostream>

namespace {

constexpr const char* accessor_type_strings[] = {"SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4"};

}  // namespace

namespace Ps::Graphics {

std::string_view BufferView::to_string(BufferView::Target target)
{
    switch (target) {
        case BufferView::Target::array_buffrer:
            return "ARRAY_BUFFER";
        case BufferView::Target::element_array_buffer:
            return "ELEMENT_ARRAY_BUFFER";
    }
    return "";
}

Accessor::Type Accessor::to_type(std::string_view str)
{
    const auto size = sizeof(accessor_type_strings) / sizeof(accessor_type_strings[0]);
    for (size_t i = 0; i < size; ++i) {
        if (accessor_type_strings[i] == str) {
            return static_cast<Accessor::Type>(i);
        }
    }
    return Accessor::Type::scalar;
}

std::string_view Accessor::to_string(Type type)
{
    switch (type) {
        case Accessor::Type::scalar:
            return accessor_type_strings[static_cast<int>(Accessor::Type::scalar)];
        case Accessor::Type::vec2:
            return accessor_type_strings[static_cast<int>(Accessor::Type::vec2)];
        case Accessor::Type::vec3:
            return accessor_type_strings[static_cast<int>(Accessor::Type::vec3)];
        case Accessor::Type::vec4:
            return accessor_type_strings[static_cast<int>(Accessor::Type::vec4)];
        case Accessor::Type::mat2:
            return accessor_type_strings[static_cast<int>(Accessor::Type::mat2)];
        case Accessor::Type::mat3:
            return accessor_type_strings[static_cast<int>(Accessor::Type::mat3)];
        case Accessor::Type::mat4:
            return accessor_type_strings[static_cast<int>(Accessor::Type::mat4)];
    }
    return "";
}

GlTF::GlTF(const std::filesystem::path& file_path)
    : file_path_{file_path}
{
    std::ifstream gltf_stream{file_path_};
    if (!gltf_stream.is_open()) {
#ifdef __llvm__
        throw std::runtime_error{fmt::format("Could not open {}", file_path_.string())};
#else
        throw std::runtime_error{std::format("Could not open {}", file_path_.string())};
#endif
    }

    nlohmann::json gltf_json;
    try {
        gltf_json = gltf_json.parse(gltf_stream);
    }
    catch (std::exception& err) {
        SPDLOG_ERROR("JSON parse error: {}", err.what());
#ifdef __llvm__
        throw std::runtime_error{fmt::format("Could not parse {} as JSON", file_path_.string())};
#else
        throw std::runtime_error{std::format("Could not parse {} as JSON", file_path_.string())};
#endif
    }

    try {
        const auto scene = gltf_json.at("scene").get<int>();
        SPDLOG_INFO("Scene: {}", scene);

        const auto& buffers_json = gltf_json.at("buffers");
        read_buffers(buffers_json);

        const auto& buffer_views_json = gltf_json.at("bufferViews");
        read_buffer_views(buffer_views_json);

        const auto& accessors_json = gltf_json.at("accessors");
        read_accessors(accessors_json);

        const auto& meshes_json = gltf_json.at("meshes");
        read_meshes(meshes_json);
    }
    catch (std::exception& err) {
        SPDLOG_ERROR("Exception: {}", err.what());
        throw std::runtime_error{"Could not construct GlTF object"};
    }
}

void GlTF::read_buffers(const nlohmann::json& buffers_json)
{
    for (const auto& buf_json : buffers_json) {
        const auto uri = buf_json.at("uri").get<std::string_view>();
        const auto byte_length = buf_json.at("byteLength").get<uint32_t>();
        if (uri.starts_with("data:")) {  // inline data
            buffers_.emplace_back(read_buffer_from_inline_data(uri, byte_length));
        }
        else {  // external file
            buffers_.emplace_back(read_buffer_from_file(uri, byte_length));
        }
    }
}

Buffer GlTF::read_buffer_from_inline_data(std::string_view data, uint32_t byte_length)
{
    if (data.find(";base64") == std::string_view::npos) {
        throw std::runtime_error{"Only Base64 data handled now!"};
    }

    const auto pos = data.find(",");
    auto base64_str = data.substr(pos + 1);  // it's ok if it throws

    auto buf = Core::base64_decode(base64_str);
    if (buf.size() != byte_length) {
        throw std::runtime_error{"Base64 data size don't match byte length."};
    }

    return buf;
}

Buffer GlTF::read_buffer_from_file(std::string_view uri, uint32_t byte_length)
{
    Buffer buff;
    buff.reserve(byte_length);
    std::ifstream bin_stream(file_path_.parent_path() / uri, std::ios::binary);
    if (!bin_stream.is_open()) {
        throw std::runtime_error{"Could not open binary file"};
    }
    buff.assign(std::istreambuf_iterator<char>(bin_stream), {});
    if (buff.size() != byte_length) {
        throw std::runtime_error{"Base64 data size don't match byte length."};
    }

    draco::PointCloud pc;
    const uint32_t pos_att_id =
      pc.GetNamedAttributeId(draco::GeometryAttribute::POSITION);
    pc.set_num_points(byte_length);

    return buff;
}

void GlTF::read_buffer_views(const nlohmann::json& buffer_views_json)
{
    for (const auto& buf_view_json : buffer_views_json) {
        const auto buf_index = buf_view_json.at("buffer").get<uint32_t>();
        const auto byte_offset = buf_view_json.at("byteOffset").get<uint32_t>();
        const auto byte_length = buf_view_json.at("byteLength").get<uint32_t>();

        auto& buf = buffers_.at(buf_index);
        if (byte_offset + byte_length > buf.size()) {
            throw std::out_of_range{"Buffer view offset + length is greater than buffer size"};
        }
        const auto buff_view = std::span<unsigned char>{&buf[byte_offset], byte_length};

        const auto target_val = buf_view_json.at("target").get<uint32_t>();
        const auto target = static_cast<BufferView::Target>(target_val);
        SPDLOG_INFO("Target: {}", BufferView::to_string(target));

        buffer_views_.emplace_back(buff_view, target);
    }
}

void GlTF::read_accessors(const nlohmann::json& accessors_json)
{
    for (const auto& accessor_json : accessors_json) {
        const auto buf_view_index = accessor_json.at("bufferView").get<uint32_t>();
        const auto& buffer_view = buffer_views_.at(buf_view_index);

        const auto byte_offset = accessor_json.at("byteOffset").get<uint32_t>();

        const auto type_str = accessor_json.at("type").get<std::string_view>();
        const auto type = Accessor::to_type(type_str);

        const auto ct_val = accessor_json.at("componentType").get<int32_t>();
        const auto ct = static_cast<Accessor::ComponentType>(ct_val);

        const auto count = accessor_json.at("count").get<uint32_t>();

        accessors_.emplace_back(buffer_view, byte_offset, type, ct, count);
    }

    for (const auto& accessor : accessors_) {
        if (accessor.type == Accessor::Type::scalar &&
            accessor.component_type == Accessor::ComponentType::ct_unsigned_short) {
            const auto* indices = reinterpret_cast<const unsigned short*>(accessor.buffer_view.buff_view.data());
            for (uint32_t i = 0; i < accessor.count; ++i) {
                SPDLOG_INFO("Index: {}", *indices);
                ++indices;
            }
        }
        else if (accessor.type == Accessor::Type::vec3 &&
                 accessor.component_type == Accessor::ComponentType::ct_float) {
            const auto* vertices_buf = reinterpret_cast<const float*>(accessor.buffer_view.buff_view.data());
            for (uint32_t i = 0; i < accessor.count; ++i) {
                Eigen::Vector3f v{vertices_buf};
                SPDLOG_INFO("Vertex: [{}, {}, {}]", v.x(), v.y(), v.z());
                vertices_buf += 3;
            }
        }
    }
}

void GlTF::read_meshes(const nlohmann::json& meshes_json)
{
    for (const auto& mesh_json : meshes_json) {
        const auto& primitives_json = mesh_json.at("primitives");
        for (const auto& primitive_json : primitives_json) {
            const auto& attributes_json = primitive_json.at("attributes");
            const auto pos_index = attributes_json.at("POSITION").get<uint32_t>();
            SPDLOG_INFO("POSITION: {}", pos_index);
            const auto& pos_accessor = accessors_.at(pos_index);

            const auto indices_index = primitive_json.at("indices").get<uint32_t>();
            SPDLOG_INFO("indices: {}", indices_index);
            const auto& indices_accessor = accessors_.at(indices_index);

            meshes_.emplace_back(&pos_accessor, nullptr, &indices_accessor);
        }
    }
}

}  // namespace Ps::Graphics
