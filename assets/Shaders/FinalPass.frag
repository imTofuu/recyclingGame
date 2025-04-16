#version 410 core

in vec2 f_uv;

uniform sampler2D u_buffer;

out vec4 out_fragColor;

void main() {
    out_fragColor = texture(u_buffer, f_uv);
}