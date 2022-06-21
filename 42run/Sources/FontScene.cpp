//
// Created by ebona on 14.06.2022.
//

//
// Created by ebona on 29.05.2022.
//

#include "Engine.hpp"

using namespace ft;

class FontScene : public Engine
{   using Engine::Engine;

    Ref<GameObject> room = scene->addGameObject(new GameObject(
        "Room",
        new Model("/42run/Models/8x8x8/8x8x8.obj"),
        new Texture("/42run/Models/8x8x8/8x8x8.png")
    ));

    Ref<GameObject> timeLabel = scene->addGameObject(new GameObject(
            "TimeLabel",
            new Text("Time: ", glm::vec3(0.0f, 32.0f, 0.0f), new Font("/42run/Textures/Font/BasicFont.bmp", 32, 32))
    ));

    Ref<GameObject> timeValue = scene->addGameObject(new GameObject(
        "Time",
        new Text("Hello, world!", glm::vec3(160.0f, 32.0f, 0.0f), new Font("/42run/Textures/Font/BasicFont.bmp", 32, 32))
    ));

    void onKeyEvent(Ref<Event>& event) override {
        if (event->getEventType() == EventType::KeyPress)
        {
            Ref<KeyPressEvent> keyPressEvent = dynamic_pointer_cast<KeyPressEvent>(event);
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

    }

    void update() override {
        timeValue->text()->update(to_string((int)time->time()));
    }
};

//int main()
//{
//    FontScene fontScene("Font Scene", 800, 600);
//    fontScene.loop();
//}