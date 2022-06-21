#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform vec3 screen;

void main()
{
    gl_Position = vec4((aPos.x / screen.x) * 2 - 1, (aPos.y / screen.y) * 2 - 1, 0.0f, 1.0f);
    TexCoord = aTexCoord;
}