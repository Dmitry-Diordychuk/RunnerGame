//
// Created by ebona on 13.05.2022.
//


#include "Engine.hpp"

using namespace ft;

class PhysicsScene : public Engine
{   using Engine::Engine;

    Ref<GameObject> skull = scene->addGameObject(new GameObject(
            "Skull",
            new Model("/42run/Models/Skull/source/skull.obj"),
            new Texture("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg"),
            ColliderType::AABB
    ));

    Ref<GameObject> floor = scene->addGameObject(new GameObject(
            "Floor",
            new AABBCollider(glm::vec3(0.0f, 0.0f, 0.0f), 5.0f, 1.0f, 5.0f, [](){
                std::cout << "Hello, collider!" << std::endl;
            })
    ));

    void onKeyEvent(std::shared_ptr<Event>& event) override {
        if (event->getEventType() == EventType::KeyPress)
        {
            std::shared_ptr<KeyPressEvent> keyPressEvent = std::dynamic_pointer_cast<KeyPressEvent>(event);
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
        floor->transform()->translate(glm::vec3(30.0f, 0.0f, 0.0f));
    }

    void start() override {
        skull->rigidBody()->setVelocity(glm::vec3(5.0f, 7.0f, 0.0f));
        skull->rigidBody()->setAcceleration(glm::vec3(0, -2.0, 0));

        camera->transform()->translate(glm::vec3(17.0f, 0.0f, 60.0f));
    }

    void update() override {

    }
};

int main()
{
    PhysicsScene physicsScene("Game Object Scene", 800, 600);
    physicsScene.loop();
}