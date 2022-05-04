//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Engine.hpp"

using namespace ft;

class Square : public Engine
{   using Engine::Engine;

    Shader shader;
    VertexBuffer vertexBuffer;
    ElementBuffer indexBuffer;
    VertexArray vertexArray;

    const GLfloat vertices[12] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f, 0.5f,0.0f
    };

    const GLuint indices[6] = {
        0, 1, 2,
        1, 2, 3
    };

    void start() override {
        shader.attach("/42run/Shaders/basic.vert");
        shader.attach("/42run/Shaders/basic.frag");
        shader.link();

        vertexBuffer.bind();
        vertexBuffer.load(vertices, 12);

        VertexBufferLayout layout;
        layout.push<GLfloat>(3);
        vertexArray.addBuffer(vertexBuffer, layout);

        indexBuffer.bind();
        indexBuffer.load(indices, 6);
    }

    void update() override {
        renderer->draw(shader, vertexArray, indexBuffer);
    }
};

//int main()
//{
//    Square square("Square", 800, 600);
//    square.loop();
//}