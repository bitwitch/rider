#version 330 core

out vec4 frag_color;

in vec2 uv;

uniform vec4 color;
uniform sampler2D texture_id;

void main() {
    frag_color = texture(texture_id, uv) * color;    
}
