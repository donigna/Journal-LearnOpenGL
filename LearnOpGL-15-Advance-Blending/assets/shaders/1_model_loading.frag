#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D texture_diffuse1;
uniform vec3 lightPos;
uniform vec3 lightColor;

float near = 0.1;
float far = 1000.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main() {
    vec3 texColor = texture(texture_diffuse1, TexCoords).rgb;

    // Lighting
    float ambientStrenght = 0.5f;
    vec3 ambient = ambientStrenght * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = texColor * (ambient + diffuse);

    // Depth Testing
    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    FragColor = vec4(texColor, 1.0f);
}
