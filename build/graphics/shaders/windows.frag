#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D diffuse0;

void main()
{
    // Discards all fragments with alpha less than 0.1.
    if (texture(diffuse0, texCoord).a < 0.1)
        discard;
    // Outputs final color.
    FragColor = texture(diffuse0, texCoord);
}