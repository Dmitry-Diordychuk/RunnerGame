//
// Created by ebona on 04.05.2022.
//

#include "Engine.hpp"


using namespace ft;

class BoxTransformScene : public Engine
{   using Engine::Engine;

    Shader shader;
    VertexBuffer vertexBuffer;
    ElementBuffer indexBuffer;
    VertexArray vertexArray;
    Texture texture;

    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float)window->getProps().width/(float)window->getProps().height,
            0.1f,
            100.0f);

    Transform transform;

    const GLfloat vertices[6 * (12 + 12 + 8)] = {
         // Texture                  Color                  Texture coordinates
            -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,

             0.5f, -0.5f, -0.5f,     1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,     0.0f, 1.0f, 0.0f,      0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,     0.0f, 0.0f, 1.0f,      1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,     1.0f, 1.0f, 0.0f,      1.0f, 1.0f,
    };

    const GLuint indices[6 * 6] = {
            0, 1, 2,
            1, 2, 3,

            4, 5, 6,
            5, 6, 7,

            8, 9, 10,
            9, 10, 11,

            12, 13, 14,
            13, 14, 15,

            16, 17, 18,
            17, 18, 19,

            20, 21, 22,
            21, 22, 23
    };

    void start() override {
        shader.attach("/42run/Shaders/transform.vert");
        shader.attach("/42run/Shaders/texture.frag");
        shader.link();

        texture.load("/42run/Textures/checker.png");

        vertexBuffer.bind();
        vertexBuffer.load(vertices, (12 + 12 + 8) * 6);

        VertexBufferLayout layout;
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(2);
        vertexArray.addBuffer(vertexBuffer, layout);

        indexBuffer.bind();
        indexBuffer.load(indices, 6 * 6);

        transform.translate(glm::vec3(-4.0f, 0.0f, -10.0f));
    }


    void update() override {
        transform.rotate(glm::vec3(0.01f, 0.01f ,0.0f));
        transform.translate(glm::vec3(2 * glm::sin(time->time()) * time->deltaTime(), 0.0f, 0.0f));
        transform.scale(glm::vec3(1.0f, 1.0f, 1.0f) * (1 + glm::sin(time->time())));

        shader.activate();
        shader.bind("projection", projectionMatrix);
        shader.bind("transform", transform.model());

        texture.bind(0);

        renderer->draw(shader, vertexArray, indexBuffer);
    }
};

int main()
{
    BoxTransformScene box("Box Transform Scene", 800, 600);
    box.loop();
}