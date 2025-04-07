#version 410 core

uniform vec3 u_lightColour;

out vec4 out_fragColor;

void main() {
    out_fragColor = vec4(u_lightColour, 1.0);
}