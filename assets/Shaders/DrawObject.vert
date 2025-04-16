#version 410 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texCoord;

uniform mat4 u_PVMatrix;
uniform mat4 u_modelMatrix;

out vec3 f_fragPos;
out vec3 f_normal;
out vec2 f_texCoord;

void main() {
    gl_Position = u_PVMatrix * u_modelMatrix * vec4(in_pos, 1.0);
    
    f_fragPos = vec3(u_modelMatrix * vec4(in_pos, 1.0));
    f_normal = in_normal;
    f_texCoord = in_texCoord;
}