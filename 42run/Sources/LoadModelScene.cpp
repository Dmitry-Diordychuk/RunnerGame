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
    //Model model = Model("/42run/Models/Cubes.obj");

    std::vector<std::unique_ptr<VertexBuffer>> vertexBuffers;
    std::vector<std::unique_ptr<ElementBuffer>> indexBuffers;
    std::vector<std::unique_ptr<VertexArray>> vertexArrays;

    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float)window->getProps().width/(float)window->getProps().height,
            0.1f,
            100.0f);

    Transform transform;

    void start() override {
        shader.attach("/42run/Shaders/transform.vert");
        shader.attach("/42run/Shaders/texture.frag");
        shader.link();

        texture.load("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg");

        for (auto& it: model)
        {
            std::vector<Vertex> vertices = it.vertices();
            std::vector<GLuint> indices = it.indices();

            std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>();
            vertexBuffer->bind();
            vertexBuffer->load((GLfloat*)&vertices[0], vertices.size() * (3 + 3 + 2));

            VertexBufferLayout layout;
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(2);

            std::unique_ptr<VertexArray> vertexArray = std::make_unique<VertexArray>();
            vertexArray->addBuffer(*vertexBuffer, layout);

            std::unique_ptr<ElementBuffer> indexBuffer = std::make_unique<ElementBuffer>();
            indexBuffer->bind();
            indexBuffer->load(&indices[0], indices.size());

            vertexBuffers.push_back(std::move(vertexBuffer));
            vertexArrays.push_back(std::move(vertexArray));
            indexBuffers.push_back(std::move(indexBuffer));
        }

        transform.translate(glm::vec3(0.0f, 0.0f, -3.0f));
    }

    void update() override {
        transform.rotate(glm::vec3(0.0f, 0.01f ,0.0f));

        shader.activate();
        shader.bind("projection", projectionMatrix);
        shader.bind("transform", transform.model());

        texture.bind(0);

        for (int i = 0; i < vertexArrays.size(); i++) {
            renderer->draw(shader, *vertexArrays[i], *indexBuffers[i]);
        }
    }
};

int main()
{
    LoadModelScene loadModelScene("Load Model Scene", 800, 600);
    loadModelScene.loop();
}