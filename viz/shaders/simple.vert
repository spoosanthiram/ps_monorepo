#version 430 core

layout(location = 0) in vec3 vertex_position;
// layout(location = 1) in vec3 vertex_normal;
// layout(location = 1) in vec4 vertex_color;
// layout(location = 2) in vec2 vertex_texture_coord;

uniform mat4 projection_matrix;
uniform mat4 model_view_matrix;

//out vec4 vertex;
//out vec4 normal;
out vec4 color; // output a color to the fragment shader
// out vec2 texture_coord;

void main()
{
    // vertex = model_view_matrix * vec4(vertex_position, 1.0f);
    // normal = model_view_matrix * vec4(vertex_normal, 0.0);
    // color = vertex_color;

    gl_Position = projection_matrix * model_view_matrix * vec4(vertex_position, 1.0f);

    // gl_Position = /*projection_matrix * */vec4(vertex_position, 1.0f);
    color = vec4(1.0, 0.0, 0.0, 1.0);
    // texture_coord = vertex_texture_coord;
}
