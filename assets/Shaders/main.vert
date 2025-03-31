#version 410 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 PVMMatrix;

out vec2 TexCoord;

void main() {
    gl_Position = PVMMatrix * vec4(aPos, 1.0);
    
    TexCoord = inTexCoord;
}