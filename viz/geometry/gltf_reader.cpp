#include "gltf_reader.h"

#include "core/utils/Base64.h"

#include <Eigen/Core>
#include <spdlog/spdlog.h>

#include <format>
#include <fstream>
#include <iostream>

namespace {

constexpr const char* accessor_type_strings[] = {"SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4"};

} // namespace

namespace ps::viz {

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
    try {
        simdjson::ondemand::parser parser;
        auto json = simdjson::padded_string::load(file_path.string());
        simdjson::ondemand::document doc = parser.iterate(json);

        const int32_t scene = doc["scene"].get_int32();
        SPDLOG_INFO("Scene: {}", scene);

        simdjson::ondemand::array buffers = doc["buffers"];
        read_buffers(buffers);

        simdjson::ondemand::array buffer_views = doc["bufferViews"];
        read_buffer_views(buffer_views);

        simdjson::ondemand::array accessors = doc["accessors"];
        read_accessors(accessors);

        simdjson::ondemand::array meshes = doc["meshes"];
        read_meshes(meshes);
    }
    catch (std::exception& err) {
        SPDLOG_ERROR("Exception: {}", err.what());
        throw std::runtime_error{"Could not construct GlTF object"};
    }
}

void GlTF::read_buffers(simdjson::ondemand::array buffers)
{
    for (auto buff : buffers) {
        const std::string_view uri = buff["uri"];
        const uint32_t byte_length = buff["byteLength"].get_uint32();
        SPDLOG_INFO("byte_length: {}", byte_length);
        if (uri.starts_with("data:")) { // inline data
            buffers_.emplace_back(read_buffer_from_inline_data(uri, byte_length));
        }
        else { // external file
            // TODO(AL-31): buffers_.emplace_back(read_buffer_from_file(uri, byte_length));
            throw std::runtime_error{"No implemented yet!"};
        }
    }
}

Buffer GlTF::read_buffer_from_inline_data(std::string_view data, uint32_t byte_length)
{
    if (data.find(";base64") == std::string_view::npos) {
        throw std::runtime_error{"Only Base64 data handled now!"};
    }

    const auto pos = data.find(",");
    auto base64_str = data.substr(pos + 1); // it's ok if it throws

    auto buf = Ps::Core::base64_decode(base64_str);
    if (buf.size() != byte_length) {
        throw std::runtime_error{"Base64 data size don't match byte length."};
    }

    return buf;
}

/*
TODO(AL-31): need to add bazel rules for draco
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
*/

void GlTF::read_buffer_views(simdjson::ondemand::array buffer_views)
{
    for (auto buf_view_obj : buffer_views) {
        const uint32_t buf_index = buf_view_obj["buffer"].get_uint32();
        const uint32_t byte_offset = buf_view_obj["byteOffset"].get_uint32();
        const uint32_t byte_length = buf_view_obj["byteLength"].get_uint32();

        auto& buf = buffers_.at(buf_index);
        if (byte_offset + byte_length > buf.size()) {
            throw std::out_of_range{"Buffer view offset + length is greater than buffer size"};
        }
        const auto buff_view = std::span<unsigned char>{&buf[byte_offset], byte_length};

        const uint32_t target_val = buf_view_obj["target"].get_uint32();
        const auto target = static_cast<BufferView::Target>(target_val);
        SPDLOG_INFO("Target: {}", BufferView::to_string(target));

        buffer_views_.emplace_back(buff_view, target);
    }
}

void GlTF::read_accessors(simdjson::ondemand::array accessors)
{
    for (auto accessor_obj : accessors) {
        const uint32_t buf_view_index = accessor_obj["bufferView"].get_uint32();
        const auto& buffer_view = buffer_views_.at(buf_view_index);

        const uint32_t byte_offset = accessor_obj["byteOffset"].get_uint32();

        const std::string_view type_str = accessor_obj["type"];
        const auto type = Accessor::to_type(type_str);

        const int32_t ct_val = accessor_obj["componentType"].get_int32();
        const auto ct = static_cast<Accessor::ComponentType>(ct_val);

        const uint32_t count = accessor_obj["count"].get_uint32();

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

void GlTF::read_meshes(simdjson::ondemand::array meshes)
{
    for (auto mesh : meshes) {
        simdjson::ondemand::array primitives = mesh["primitives"];
        for (auto primitive : primitives) {
            auto attributes = primitive["attributes"];
            const uint32_t pos_index = attributes["POSITION"].get_uint32();
            SPDLOG_INFO("POSITION: {}", pos_index);
            const auto& pos_accessor = accessors_.at(pos_index);

            const uint32_t indices_index = primitive["indices"].get_uint32();
            SPDLOG_INFO("indices: {}", indices_index);
            const auto& indices_accessor = accessors_.at(indices_index);

            meshes_.emplace_back(&pos_accessor, nullptr, &indices_accessor);
        }
    }
}

} // namespace ps::viz
