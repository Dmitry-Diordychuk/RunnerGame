//
// Created by ebona on 12.05.2022.
//

#include "Engine.hpp"

using namespace ft;

class GameObjectScene : public Engine
{   using Engine::Engine;

    Ref<GameObject> skull = scene->addGameObject(new GameObject(
        "Skull",
        new Model("/42run/Models/Skull/source/skull.obj"),
        new Texture("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg")
    ));

    Ref<GameObject> skull2 = scene->addGameObject(new GameObject(
        "Skull2",
        new Model("/42run/Models/Skull/source/skull.obj"),
        new Texture("/42run/Models/Skull/textures/difuso_flip_oscuro.jpg")
    ));

    Ref<GameObject> room = scene->addGameObject(new GameObject(
        "Room",
        new Model("/42run/Models/8x8x8/8x8x8.obj"),
        new Texture("/42run/Models/8x8x8/8x8x8.png")
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
    }

    void start() override {
        skull->transform()->translate(glm::vec3(0.0f, 0.0f, -5.0f));

        skull2->transform()->translate(glm::vec3(2.0f, 0.0f, -5.0f));
        room->transform()->translate(glm::vec3(-3.0f, -5.0f, -1.5f));
        room->transform()->scale(glm::vec3(8.0f, 8.0f, 8.0f));
    }

    void update() override {
        skull->transform()->rotate(glm::vec3(0.0f, 0.01f, 0.0));
        skull2->transform()->rotate(glm::vec3(0.0f, -9.8f, 0.0));
    }
};

//int main()
//{
//    GameObjectScene gameObjectScene("Game Object Scene", 800, 600);
//    gameObjectScene.loop();
//}