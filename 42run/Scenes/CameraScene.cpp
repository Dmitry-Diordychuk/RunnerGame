//
// Created by ebona on 09.05.2022.
//

#include "Engine.hpp"


using namespace ft;

class CameraScene : public Engine
{   using Engine::Engine;

    Shader shader;
    Texture texture;
    Model model = Model("/42run/Models/Skull/source/skull.obj");
    //Model model = Model("/42run/Models/Cubes.obj");

    vector<Scope<VertexBuffer>> vertexBuffers;
    vector<Scope<ElementBuffer>> indexBuffers;
    vector<Scope<VertexArray>> vertexArrays;

    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float)window->getProps().width/(float)window->getProps().height,
            0.1f,
            100.0f);

    Transform transform;

    void onWindowEvent(Ref<Event>& event) override {
        if (event->getEventType() == EventType::WindowResize)
        {
            Ref<WindowResizeEvent> windowResizeEvent = dynamic_pointer_cast<WindowResizeEvent>(event);
            cout << "Window resized width: " << windowResizeEvent->width() << " height: " << windowResizeEvent->height() << endl;
        }
        else if (event->getEventType() == EventType::WindowClose)
        {
            cout << "Window closed" << endl;
        }
    }

    void onKeyEvent(Ref<Event>& event) override {
        if (event->getEventType() == EventType::KeyPress)
        {
            Ref<KeyPressEvent> keyPressEvent = dynamic_pointer_cast<KeyPressEvent>(event);
            cout << "Key " << keyPressEvent->key() << " pressed" << endl;

            if (keyPressEvent->key() == GLFW_KEY_W)
            {
                camera->transform()->translate(glm::vec3(-camera->transform()->model()[2]) * 0.05f);
            }
            if (keyPressEvent->key() == GLFW_KEY_S)
            {
                camera->transform()->translate(glm::vec3(camera->transform()->model()[2]) * 0.05f);
            }
            if (keyPressEvent->key() == GLFW_KEY_A)
            {
                camera->transform()->rotate(glm::vec3(0.0f, +0.03f, 0.0f));
            }
            if (keyPressEvent->key() == GLFW_KEY_D)
            {
                camera->transform()->rotate(glm::vec3(0.0, -0.03f, 0.0f));
            }
            if (keyPressEvent->key() == GLFW_KEY_Q)
            {
                camera->transform()->translate(glm::vec3(-camera->transform()->model()[0]) * 0.05f);
            }
            if (keyPressEvent->key() == GLFW_KEY_E)
            {
                camera->transform()->translate(glm::vec3(camera->transform()->model()[0]) * 0.05f);
            }
        }
        else if (event->getEventType() == EventType::KeyRelease)
        {
            Ref<KeyReleaseEvent> keyReleaseEvent = dynamic_pointer_cast<KeyReleaseEvent>(event);
            cout << "Key " << keyReleaseEvent->key() << " released" << endl;
        }
    }

    void start() override {
        shader.attach("/42run/Shaders/camera.vert");
        shader.attach("/42run/Shaders/illumination.frag");
        shader.link();

        texture.load("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg");

        for (auto& it: model)
        {
            vector<Vertex> vertices = it.vertices();
            vector<GLuint> indices = it.indices();

            Scope<VertexBuffer> vertexBuffer = make_unique<VertexBuffer>();
            vertexBuffer->bind();
            vertexBuffer->load((GLfloat*)&vertices[0], vertices.size() * (3 + 3 + 2));

            VertexBufferLayout layout;
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(2);

            Scope<VertexArray> vertexArray = make_unique<VertexArray>();
            vertexArray->addBuffer(*vertexBuffer, layout);

            Scope<ElementBuffer> indexBuffer = make_unique<ElementBuffer>();
            indexBuffer->bind();
            indexBuffer->load(&indices[0], indices.size());

            vertexBuffers.push_back(move(vertexBuffer));
            vertexArrays.push_back(move(vertexArray));
            indexBuffers.push_back(move(indexBuffer));
        }

        transform.translate(glm::vec3(0.0f, 0.0f, -3.0f));
    }

    void update() override {
        //transform.rotate(glm::vec3(0.0f, 0.01f ,0.0f));

        shader.activate();
        shader.bind("projection", projectionMatrix);
        shader.bind("view", camera->transform()->inverseModel());
        shader.bind("model", transform.model());
        shader.bind("ambientLightingColor", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.bind("diffuseLightingColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.bind("lightPos", glm::vec3(3.0f, 2.0f, 0.0f));

        texture.bind(0);

        for (int i = 0; i < vertexArrays.size(); i++) {
            renderer->draw(shader, *vertexArrays[i], *indexBuffers[i]);
        }
    }
};

int main()
{
    CameraScene cameraScene("Camera Scene", 800, 600);
    cameraScene.loop();
}