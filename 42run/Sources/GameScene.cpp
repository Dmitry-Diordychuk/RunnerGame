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
        {
            new AABBCollider(false, []() {
                cout << "Player collider event!" << endl;
            })
        }
    ));

    bool isGrounded = true;
    Ref<GameObject> floorCollider = scene->addGameObject(new GameObject(
        "FloorCollider",
        {
            new AABBCollider(glm::vec3(0.0f, -31.9f, 0.0f), glm::vec3(16.0f, 16.0f, 16.0f), true,
                 [&]() {
                     if (!isGrounded) {
                         finn->transform()->rotate(glm::vec3(-finn->transform()->angle().x, 0.0f, 0.0f));
                         finn->transform()->rotate(glm::vec3(0.0f, 0.9f, 0.0f));
                         finn->rigidBody()->setAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
                     }
                     isGrounded = true;
                 })
        }
    ));

    vector<Ref<GameObject>> rooms = {
            scene->addGameObject(new GameObject(
                    "Empty",
                    new Model("/42run/Models/Empty/Empty.obj"),
                    new Texture("/42run/Models/Empty/Empty.png")
            )),
            scene->addGameObject(new GameObject(
                    "Column",
                    new Model("/42run/Models/Column/Column.obj"),
                    new Texture("/42run/Models/Column/Column.png")
            )),
            scene->addGameObject(new GameObject(
                    "LeftTable",
                    new Model("/42run/Models/LeftTable/LeftTable.obj"),
                    new Texture("/42run/Models/LeftTable/LeftTable.png")
            )),
            scene->addGameObject(new GameObject(
                    "TwoColumns",
                    new Model("/42run/Models/TwoColumns/TwoColumns.obj"),
                    new Texture("/42run/Models/TwoColumns/TwoColumns.png")
            )),
            scene->addGameObject(new GameObject(
                    "RightTable",
                    new Model("/42run/Models/RightTable/RightTable.obj"),
                    new Texture("/42run/Models/RightTable/RightTable.png")
            )),
            scene->addGameObject(new GameObject(
                    "Tunel",
                    new Model("/42run/Models/Tunel/Tunel.obj"),
                    new Texture("/42run/Models/Tunel/Tunel.png")
            )),
            scene->addGameObject(new GameObject(
                    "TwoTables",
                    new Model("/42run/Models/TwoTables/TwoTables.obj"),
                    new Texture("/42run/Models/TwoTables/TwoTables.png")
            )),
    };

    float t = 0;
    void onKeyEvent(Ref<Event>& event) override {
        if (event->getEventType() == EventType::KeyPress)
        {
            Ref<KeyPressEvent> keyPressEvent = dynamic_pointer_cast<KeyPressEvent>(event);
            if (keyPressEvent->key() == GLFW_KEY_A)
            {
                if (finn->transform()->position().x > -5.5f && finn->transform()->position().x < 5.5f) {
                    camera->transform()->translate(glm::vec3(-camera->transform()->model()[0]) * 0.2f);
                }
                if (finn->transform()->position().x > -8.5f) {
                    finn->transform()->translate(glm::vec3(-0.2f, 0.0f, 0.0f));
                }
            }
            if (keyPressEvent->key() == GLFW_KEY_D)
            {
                if (finn->transform()->position().x > -5.5f && finn->transform()->position().x < 5.5f) {
                    camera->transform()->translate(glm::vec3(camera->transform()->model()[0]) * 0.2f);
                }
                if (finn->transform()->position().x < 8.5f) {
                    finn->transform()->translate(glm::vec3(0.2f, 0.0f, 0.0f));
                }
            }
            if (keyPressEvent->key() == GLFW_KEY_SPACE && isGrounded)
            {
                finn->transform()->rotate(glm::vec3(0.0f, -finn->transform()->angle().y, 0.0f));
                finn->transform()->rotate(glm::vec3(0.0f, glm::pi<float>(), 0.0f));
                finn->rigidBody()->setVelocity(glm::vec3(0.0f, 12.5f, 0.0f));
                t = 0;
                finn->rigidBody()->setAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
                isGrounded = false;
            }
        }
    }

    void start() override {
        finn->transform()->scale(glm::vec3(0.05f, 0.05f, 0.05f));
        finn->transform()->translate(glm::vec3(0.0f, 0.1f, 0.0f));
        finn->transform()->rotate(glm::vec3(0.0f, glm::pi<float>(), 0.0f));

        camera->transform()->translate(glm::vec3(0.0f, 9.0f, 9.0f));
        camera->transform()->rotate(glm::vec3(-0.5f, 0.0f, 0.0f));
        //camera->transform()->translate(glm::vec3(0.0f, 40.0f, 100.5f));
        //camera->transform()->translate(glm::vec3(0.0f, -10.0f, 30.0f));

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->transform()->translate(glm::vec3(0.0f, 2.0f, i * -7.8f));
        }
    }

    void update() override {
        if (!isGrounded) {
            finn->transform()->rotate(glm::vec3(-0.09f, 0.0f, 0.0f));
        } else {
            t += time->deltaTime();
            finn->transform()->rotate(glm::vec3(0.0f, -glm::sin(t * 5) / 5, 0.0f));
        }

        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i]->transform()->position().z < 7.8f) {
                rooms[i]->transform()->translate(glm::vec3(0.0f, 0.0f, 0.1f));
            } else {
                rooms[i]->transform()->position(glm::vec3(0.0f, 2.0f, -7.8 * (rooms.size() - 1)));
            }
        }
    }
};

int main()
{
    GameScene physicsScene("Game Scene", 800, 600);
    physicsScene.loop();
}