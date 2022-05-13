#version 430 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec3 ambientLightingColor;
uniform vec3 diffuseLightingColor;
uniform vec3 lightPos;

void main()
{
    float ambientStreangth = 0.1;
    vec3 ambient = ambientStreangth * ambientLightingColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * diffuseLightingColor;

    FragColor = vec4(ambient + diffuse, 1.0) * texture(ourTexture, TexCoord);
}