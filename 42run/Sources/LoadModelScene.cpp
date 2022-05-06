//
// Created by ebona on 05.05.2022.
//

#include "Engine.hpp"


using namespace ft;

class LoadModelScene : public Engine
{   using Engine::Engine;

    Shader shader;
    Texture texture;
    Model model = Model("/42run/Models/Skull/source/skull.obj");

    VertexBuffer vertexBuffer;
    ElementBuffer indexBuffer;
    VertexArray vertexArray;

    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float)window->getProps().width/(float)window->getProps().height,
            0.1f,
            100.0f);

    Transform transform;

    void start() override {
        shader.attach("/42run/Shaders/normal.vert");
        shader.attach("/42run/Shaders/normal.frag");
        shader.link();

        texture.load("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg");

        for (auto& it: model)
        {
            std::vector<Vertex> vertices = it.vertices();
            std::vector<GLuint> indices = it.indices();

            vertexBuffer.bind();
            vertexBuffer.load((GLfloat*)&vertices[0], vertices.size() * (3 + 3 + 2));

            VertexBufferLayout layout;
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(2);
            vertexArray.addBuffer(vertexBuffer, layout);

            indexBuffer.bind();
            indexBuffer.load(&indices[0], indices.size());
        }

        transform.translate(glm::vec3(0.0f, 0.0f, -3.0f));
    }

    void update() override {
        transform.rotate(glm::vec3(0.0f, 0.01f ,0.0f));

        shader.activate();
        shader.bind("projection", projectionMatrix);
        shader.bind("model", transform.model());

        texture.bind(0);

        renderer->draw(shader, vertexArray, indexBuffer);
    }
};

int main()
{
    LoadModelScene loadModelScene("Load Model Scene", 800, 600);
    loadModelScene.loop();
}