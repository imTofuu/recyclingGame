#version 410 core

in vec3 f_fragPos;
in vec3 f_normal;
in vec2 f_texCoord;

out vec4 out_fragColor;

uniform sampler2D u_tex;

uniform float u_ambientStrength;
uniform vec3 u_ambientColour;

void main() {

    vec3 ambient = u_ambientStrength * u_ambientColour;
    vec4 textureSample = texture(u_tex, f_texCoord);
    
    vec3 result = ambient * textureSample.rgb;
    
    out_fragColor = vec4(result, textureSample.a);
}