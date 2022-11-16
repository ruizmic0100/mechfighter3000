#version 330 core

// Outputs colors in RGBA.
out vec4 FragColor;

// Imports the current position from the Vertex Shader.
in vec3 crntPos;
// Imports the normal from the Vertex Shader.
in vec3 Normal;
// Imports the color from the Vertex Shader.
in vec3 color;
// Imports the texture coordinates from the Vertex Shader.
in vec2 texCoord;

// Gets the Texture Units from the main function.
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light from the main function.
uniform vec4 lightColor;
// Gets the position of the light from the main function.
uniform vec3 lightPos;
// Gets the position of the camera from the main function.
uniform vec3 camPos;

vec4 directLight()
{
    // Ambient lighting.
    float ambient = 0.20f;

    // Diffuse lighting.
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(abs(dot(normal, lightDirection)), 0.0f); // Absolute helps with grass shading!

    // Specular lighting.
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // Discards all fragments with alpha less that 0.1.
    if (texture(diffuse0, texCoord).a < 0.1)
        discard;

    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

void main()
{
    // Outputs final color.
    FragColor = directLight();
}