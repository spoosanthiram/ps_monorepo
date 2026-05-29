#version 430 core

//in vec4 vertex;
//in vec4 normal;
in vec4 color;
// in vec2 texture_coord;

//const vec4 ambient_light = vec4(0.1, 0.1, 0.1, 0.0);
//const vec3 light_position = vec3(0.0, 0.0, 5.0);
//const vec4 light_diffuse_color = vec4(0.9, 0.9, 0.9, 1.0);

// uniform sampler2D our_texture;

out vec4 frag_color;

void main()
{
//    vec3 normal_vec = normalize(vec3(normal));
//    vec3 light_dir = normalize(light_position - vertex.xyz);
//    vec4 diffuse_component = light_diffuse_color * color * max(dot(normal_vec, light_dir), 0.0);

//    frag_color = min(ambient_light + diffuse_component, vec4(1.0));

    // frag_color = texture(our_texture, texture_coord) * color;

    frag_color = color;
}
