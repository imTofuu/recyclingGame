#version 410 core

layout(location = 0) in vec3 aPos;

uniform mat4 PVMMatrix;

void main() {
    gl_Position = PVMMatrix * vec4(aPos, 1.0);
}