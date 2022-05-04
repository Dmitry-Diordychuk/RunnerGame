//
// Created by ebona on 04.05.2022.
//

#include "Engine.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace ft;

class BoxTransformScene : public Engine
{   using Engine::Engine;

    Shader shader;
    VertexBuffer vertexBuffer;
    ElementBuffer indexBuffer;
    VertexArray vertexArray;
    Texture texture;
    glm::mat4 transformMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);

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
        glEnable(GL_DEPTH_TEST);

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

        WindowProps props = window->getProps();
        glViewport(0, 0, props.width, props.height);
        projectionMatrix = glm::perspective(
                glm::radians(45.0f),
                (float)props.width/(float)props.height,
                0.1f, 100.0f);
    }

    void update() override {
        transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
        transformMatrix = glm::rotate(transformMatrix, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        shader.activate();
        shader.bind("transform", projectionMatrix * transformMatrix);

        texture.bind(0);

        renderer->draw(shader, vertexArray, indexBuffer);
    }
};

int main()
{
    BoxTransformScene box("Box Transform Scene", 800, 600);
    box.loop();
}