#pragma once

#include <nlohmann/json_fwd.hpp>

#include <filesystem>
#include <span>
#include <string_view>
#include <vector>

namespace Ps::Graphics {

using Buffer = std::vector<unsigned char>;

struct BufferView
{
    enum class Target : int32_t
    {
        array_buffrer = 34962,
        element_array_buffer = 34963
    };
    static std::string_view to_string(Target target);

    BufferView(std::span<unsigned char> bv, Target t)
        : buff_view{bv}
        , target{t}
    {}

    std::span<unsigned char> buff_view;
    Target target;
};

struct Accessor
{
    enum class Type
    {
        scalar,
        vec2,
        vec3,
        vec4,
        mat2,
        mat3,
        mat4
    };
    static Type to_type(std::string_view str);
    static std::string_view to_string(Type type);

    enum class ComponentType : int32_t
    {
        ct_byte = 5120,
        ct_unsigned_byte = 5121,
        ct_short = 5122,
        ct_unsigned_short = 5123,
        ct_unsigned_int = 5125,
        ct_float = 5126,
    };

    Accessor(const BufferView& bv, uint32_t offset, Type t, ComponentType ct, uint32_t c)
        : buffer_view{bv}
        , byte_offset{offset}
        , type{t}
        , component_type{ct}
        , count{c}
    {}

    const BufferView& buffer_view;
    uint32_t byte_offset;
    Type type;
    ComponentType component_type;
    uint32_t count;
};

struct Mesh
{
    Mesh(const Accessor* p, const Accessor* n, const Accessor* i)
        : position{p}
        , normal{n}
        , indices{i}
    {}
    const Accessor* position{nullptr};
    const Accessor* normal{nullptr};
    const Accessor* indices{nullptr};
};

class GlTF
{
public:
    GlTF(const std::filesystem::path& file_path);

    const std::vector<Mesh>& get_meshes() const { return meshes_; }

private:
    void read_buffers(const nlohmann::json& buffers_json);
    Buffer read_buffer_from_inline_data(std::string_view data, uint32_t byte_length);
    Buffer read_buffer_from_file(std::string_view uri, uint32_t byte_length);

    void read_buffer_views(const nlohmann::json& buffer_views_json);

    void read_accessors(const nlohmann::json& accessors_json);

    void read_meshes(const nlohmann::json& meshes_json);

private:
    std::filesystem::path file_path_;
    std::vector<Buffer> buffers_;
    std::vector<BufferView> buffer_views_;
    std::vector<Accessor> accessors_;
    std::vector<Mesh> meshes_;
};

}  // namespace Ps::Graphics
