//
// Created by ebona on 04.05.2022.
//

#include "Engine.hpp"

using namespace ft;

class TextureScene : public Engine
{   using Engine::Engine;

    Shader shader;
    VertexBuffer vertexBuffer;
    ElementBuffer indexBuffer;
    VertexArray vertexArray;
    Texture texture;

    const GLfloat vertices[12 + 12 + 8] = {
            // Texture                              Color                              Texture coordinates
            -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f,0.0f,    0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
            0.5f,-0.5f,0.0f,    0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
            0.5f, 0.5f,0.0f,    1.0f, 1.0f, 0.0f,  1.0f, 1.0f
    };

    const GLuint indices[6] = {
            0, 1, 2,
            1, 2, 3
    };

    void start() override {
        shader.attach("/42run/Shaders/texture.vert");
        shader.attach("/42run/Shaders/texture.frag");
        shader.link();

        vertexBuffer.bind();
        vertexBuffer.load(vertices, 12 + 12 + 8);

        texture.load("/42run/Textures/checker.png");

        VertexBufferLayout layout;
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(2);
        vertexArray.addBuffer(vertexBuffer, layout);

        indexBuffer.bind();
        indexBuffer.load(indices, 6);
    }

    void update() override {
        texture.bind(0);

        renderer->draw(shader, vertexArray, indexBuffer);
    }
};

int main()
{
    TextureScene textureScene("Texture Scene", 800, 600);
    textureScene.loop();
}