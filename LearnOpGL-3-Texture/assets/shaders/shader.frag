#version 330 core

out vec4 color;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float ourMix;

void main() {

    // ## Defaults
    // color = mix(texture2D(ourTexture1, TexCoord), texture2D(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);

    // ## EXCERCISE 1, flip foto
    // color = mix(texture2D(ourTexture1, TexCoord), texture2D(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);

    // ## EXERCISE 2, 4 foto
    color = mix(texture2D(ourTexture1, TexCoord), texture2D(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), ourMix);
}