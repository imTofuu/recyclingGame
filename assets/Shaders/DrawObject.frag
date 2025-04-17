#version 410 core

in vec3 f_fragPos;
in vec3 f_normal;
in vec2 f_texCoord;

out vec4 out_fragColor;

uniform sampler2D u_tex;

uniform mat4 u_modelMatrix;
uniform vec3 u_viewPosition;

uniform float u_ambientStrength;

struct Light {
    vec3 position;
    vec3 direction;
    vec3 colour;
    float intensity;
    float dist;
    float cutOff;
    float cutOffMargin;
    int type;
};

uniform Light u_lightInfos[MAX_DRAW_LIGHTS];

uniform struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} u_material;

vec3 calculateLightResult(Light light) {
    
    // Terms found with regression in desmos using table from Ogre3D wiki
    float linear = 5.58574 * pow(light.dist, -1.0704);
    float quadratic = 131.35334 * pow(light.dist, -2.20532);

    float distance = length(light.position - f_fragPos);
    float attenuation = light.type != 2 ? 1.0 / (1 + linear * distance + quadratic * (distance * distance)) : 1;

    vec3 normal = normalize(f_normal);
    vec3 lightDir = light.type != 2 ? normalize(light.position - f_fragPos) : normalize(-light.direction);
    vec3 viewDir = normalize(-u_viewPosition - f_fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    
    float diffuseStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * light.colour * u_material.diffuse * attenuation * light.intensity;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec3 specular = spec * light.colour * u_material.specular * attenuation * light.intensity;
    
    if(light.type == 3) {
        float theta = dot(lightDir, normalize(-light.direction));
        
        float innerCutOff = light.cutOff - light.cutOffMargin;
        float outerCutOff = light.cutOff + light.cutOffMargin;
        
        float epsilon = innerCutOff - outerCutOff;
        float intensity = clamp((theta - outerCutOff) / epsilon, 0.0, 1.0);
        diffuse *= intensity;
        specular *= intensity;
    }
    
    return diffuse + specular;
}

void main() {
    
    vec3 ambient = u_ambientStrength * u_material.ambient;
    vec4 textureSample = texture(u_tex, f_texCoord);
    
    vec3 result = ambient;
    
    for (int i = 0; i < MAX_DRAW_LIGHTS; i++) {
        
        result += calculateLightResult(u_lightInfos[i]);
    }
    
    out_fragColor = vec4(result * textureSample.rgb, textureSample.a);
}