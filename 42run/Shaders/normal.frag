#version 430 core
//out vec4 FragColor;
//
//in vec3 Normal;
//in vec3 FragPos;
//in vec2 TexCoord;
//
//uniform vec3 lightPos = vec3(0.0, 3.0, 0.0);
//uniform vec3 lightColor = vec3(0.0, 0.0, 0.0);
//uniform vec3 objectColor = vec3(0.0, 0.0, 0.0);
//
//uniform sampler2D ourTexture;
//
//void main()
//{
//    // ambient
//    float ambientStrength = 0.1;
//    vec3 ambient = ambientStrength * lightColor;
//
//    // diffuse
//    vec3 norm = normalize(Normal);
//    vec3 lightDir = normalize(lightPos - FragPos);
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = diff * lightColor;
//
//    vec3 result = (ambient + diffuse) * objectColor;
//    FragColor = texture(ourTexture, TexCoord) * vec4(result, 1.0);
//}

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}