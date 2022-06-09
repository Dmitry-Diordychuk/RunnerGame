//
// Created by ebona on 29.05.2022.
//

#include "Engine.hpp"

using namespace ft;

class GameScene : public Engine
{   using Engine::Engine;

    Ref<GameObject> finn = scene->addGameObject(new GameObject(
        "Finn",
        new Model("/42run/Models/Finn/Finn.obj"),
        new Texture("/42run/Models/Finn/Finn.png"),
        new AABBCollider(false, [](){
            cout << "Player collider event!" << endl;
        })
    ));

    bool isGrounded = true;
    Ref<GameObject> floorCollider = scene->addGameObject(new GameObject(
        "FloorCollider",
        new AABBCollider(glm::vec3(0.0f, -7.9f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f), true,
        [&](){
            if (!isGrounded) {
                finn->transform()->rotate(glm::vec3(-finn->transform()->angle().x, 0.0f, 0.0f));
                finn->transform()->rotate(glm::vec3(0.0f, 0.9f, 0.0f));
            }
            isGrounded = true;
        })
    ));

    float t = 0;
    void onKeyEvent(Ref<Event>& event) override {
        if (event->getEventType() == EventType::KeyPress)
        {
            Ref<KeyPressEvent> keyPressEvent = dynamic_pointer_cast<KeyPressEvent>(event);
            if (keyPressEvent->key() == GLFW_KEY_A)
            {
                if (finn->transform()->position().x > -2.5f) {
                    camera->transform()->translate(glm::vec3(-camera->transform()->model()[0]) * 0.05f);
                    finn->transform()->translate(glm::vec3(-0.05f, 0.0f, 0.0f));
                }
            }
            if (keyPressEvent->key() == GLFW_KEY_D)
            {
                if (finn->transform()->position().x < 2.5f) {
                    camera->transform()->translate(glm::vec3(camera->transform()->model()[0]) * 0.05f);
                    finn->transform()->translate(glm::vec3(0.05f, 0.0f, 0.0f));
                }
            }
            if (keyPressEvent->key() == GLFW_KEY_SPACE && isGrounded)
            {
                finn->transform()->rotate(glm::vec3(0.0f, -finn->transform()->angle().y, 0.0f));
                finn->transform()->rotate(glm::vec3(0.0f, glm::pi<float>(), 0.0f));
                finn->rigidBody()->setVelocity(glm::vec3(0.0f, 8.5f, 0.0f));
                t = 0;
                isGrounded = false;
            }
        }
    }

    vector<Ref<GameObject>> floors;

    void start() override {
        for (int i = 0; i < 7; i++) {
            Ref<GameObject> floor = scene->addGameObject(new GameObject(
                "Floor" + to_string(i + 1),
                new Model("/42run/Models/TwoTables/twoTables.obj"),
                new Texture("/42run/Models/TwoTables/twoTables.png"),
                new AABBCollider(glm::vec3(2.0f, -2.0f, 0.0f), glm::vec3(1.5f, 1.0f, 0.5f), true, [&](){
                    cout << time->time() << "BOOM!" << endl;
                })
            ));
            floors.push_back(floor);
        }

        finn->transform()->scale(glm::vec3(0.03f, 0.03f, 0.03f));
        finn->transform()->translate(glm::vec3(0.0f, 0.1f, 0.0f));
        finn->transform()->rotate(glm::vec3(0.0f, glm::pi<float>(), 0.0f));
        finn->rigidBody()->setAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));

        camera->transform()->translate(glm::vec3(0.0f, 5.0f, 5.45f));
        camera->transform()->rotate(glm::vec3(-0.45f, 0.0f, 0.0f));
        //camera->transform()->translate(glm::vec3(0.0f, 40.0f, 100.5f));
        //camera->transform()->translate(glm::vec3(0.0f, -2.0f, 20.0f));

        for (int i = 0; i < floors.size(); i++) {
            floors[i]->transform()->translate(glm::vec3(0.0f, 2.0f, i * -8.0f));
        }
    }

    void update() override {
        if (!isGrounded) {
            finn->transform()->rotate(glm::vec3(-0.15f, 0.0f, 0.0f));
        } else {
            t += time->deltaTime();
            finn->transform()->rotate(glm::vec3(0.0f, -glm::sin(t * 5) / 5, 0.0f));
        }

        for (int i = 0; i < floors.size(); i++) {
            if (floors[i]->transform()->position().z < 8.0f) {
                floors[i]->transform()->translate(glm::vec3(0.0f, 0.0f, 0.05f));
            } else {
                floors[i]->transform()->position(glm::vec3(0.0f, 2.0f, -8.0 * (floors.size()-1)));
            }
        }
    }
};

int main()
{
    GameScene physicsScene("Game Scene", 800, 600);
    physicsScene.loop();
}