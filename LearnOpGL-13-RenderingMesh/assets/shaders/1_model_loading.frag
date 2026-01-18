#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 lightColor;

void main() {
    float ambientStrenght = 0.5f;
    vec3 ambient = ambientStrenght * lightColor;

    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = texColor * (ambient + diffuse);
    FragColor = vec4(result, 1.0f);
}
