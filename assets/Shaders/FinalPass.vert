#version 410 core

layout(location = 0) in vec3 in_pos;
layout(location = 2) in vec2 in_uv;

out vec2 f_uv;

void main() {
    gl_Position = vec4(in_pos, 1.0);
    
    f_uv = in_uv;
}