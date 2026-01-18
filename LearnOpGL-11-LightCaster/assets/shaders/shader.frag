#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
out vec4 color;

uniform Light light;
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;
// uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {

    // Diffuse
    vec3 result;
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    if(theta > light.outerCutOff) {

        vec3 ambient = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
        vec3 norm = normalize(Normal);
        // Directional Lighting
        // vec3 lightDir = normalize(-light.direction);
        // Point Light
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * vec3(texture2D(material.diffuse, TexCoords));

        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        float specularStrength = 0.5;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * vec3(texture2D(material.specular, TexCoords));

        // Attenuation (Pengurangan intensitas cahaya berdasarkan jarak)
        float distance = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        diffuse *= intensity;
        specular *= intensity;

        result = ambient + diffuse + specular;
    } else {
        result = light.ambient * vec3(texture2D(material.diffuse, TexCoords));
    }

    color = vec4(result, 1.0);
}