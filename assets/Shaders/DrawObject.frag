#version 410 core

in vec3 f_fragPos;
in vec3 f_normal;
in vec2 f_texCoord;

out vec4 out_fragColor;

uniform sampler2D u_tex;

uniform mat4 u_modelMatrix;

uniform float u_ambientStrength;
uniform vec3 u_ambientColour;

struct Light {
    vec3 position;
    vec3 direction;
    vec3 colour;
    float intensity;
    int type;
};

uniform Light u_lightInfos[MAX_DRAW_LIGHTS];

vec3 processPointLight(in Light light) {
    
    vec3 normal = normalize(f_normal);
    vec3 lightDir = -normalize(light.position - f_fragPos);
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * light.colour * light.intensity;
    
    return diffuse;
}

vec3 processDirectionalLight(in Light light) {
    
    vec3 lightDir = normalize(light.direction);
    vec3 transformedNormal = normalize(mat3(-u_modelMatrix) * f_normal);
    
    float diff = max(dot(transformedNormal, lightDir), 0.0);
    vec3 diffuse = diff * light.colour * light.intensity;

    return diffuse;
}

void main() {
    
    vec3 ambient = u_ambientStrength * u_ambientColour;
    vec4 textureSample = texture(u_tex, f_texCoord);
    
    vec3 result = ambient;
    
    for (int i = 0; i < MAX_DRAW_LIGHTS; i++) {
        Light currentLight = u_lightInfos[i];
        
        if(currentLight.type == 0) {
            continue;
        } else if(currentLight.type == 1) { // Point light
            result += processPointLight(currentLight);
            continue;
        } else if (currentLight.type == 2) { // Directional light
            result += processDirectionalLight(currentLight);
            continue;
        } else {
            out_fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f); // Error colour
            return;
        }
    }
    
    out_fragColor = vec4(result * textureSample.rgb, /*textureSample.a*/1.0f);
}