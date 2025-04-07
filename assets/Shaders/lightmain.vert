#version 410 core

layout(location = 0) in vec3 in_pos;

uniform mat4 u_PVMMatrix;

void main() {
    gl_Position = u_PVMMatrix * vec4(in_pos, 1.0);
}