#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;

out vec2 uv;

uniform mat4 projection;
uniform mat4 model;

void main () {
    uv = a_uv;
    gl_Position = projection * model * vec4(a_pos, 1.0);
}
