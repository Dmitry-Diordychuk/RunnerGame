//
// Created by ebona on 29.05.2022.
//

#include <algorithm>
#include <random>
#include <chrono>

#include "Engine.hpp"

using namespace ft;

class GameScene : public Engine
{   using Engine::Engine;

    bool isGameOver = false;
    bool isDead = false;

    Ref<GameObject> distanceLabel = scene->addGameObject(new GameObject(
            "DistanceLabel",
            new Text("Distance: ", glm::vec3(0.0f, 1192.0f, 0.0f), new Font("/42run/Textures/Font/BasicFont.bmp", 32, 32))
    ));

    Ref<GameObject> distanceValue = scene->addGameObject(new GameObject(
            "NONE",
            new Text("Hello, world!", glm::vec3(10.0f * 32.0f, 1192.0f, 5.0f), new Font("/42run/Textures/Font/BasicFont.bmp", 32, 32))
    ));

    Ref<GameObject> finn = scene->addGameObject(new GameObject(
        "Finn",
        new Model("/42run/Models/Finn/Finn.obj"),
        new Texture("/42run/Models/Finn/Finn.png"),
        {
            new AABBCollider(glm::vec3(0.0f, 17.0f, 0.0f), glm::vec3(17.0f, 34.0f, 17.0f), false, false)
        }
    ));

    bool isGrounded = true;
    Ref<GameObject> floorCollider = scene->addGameObject(new GameObject(
        "FloorCollider",
        {
            new AABBCollider(glm::vec3(0.0f, -31.0f, 0.0f), glm::vec3(16.0f, 16.0f, 16.0f), true, false,
                [&](const Ref<Collider>&, const Ref<Collider>&) {
                     if (!isGrounded) {
                         finn->transform()->rotate(glm::vec3(-finn->transform()->angle().x, 0.0f, 0.0f));
                         finn->transform()->rotate(glm::vec3(0.0f, 0.9f, 0.0f));
                         finn->rigidBody()->setAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
                     }
                     isGrounded = true;
                })
        }
    ));

    function<void(Ref<Collider>, Ref<Collider>)> collisionFunction = [&](
        const Ref<Collider>& thisCollider,
        const Ref<Collider>& otherCollider
    ){
        cout << time->time() << " " << thisCollider->gameObject()->name() <<  " collide with " << otherCollider->gameObject()->name() << endl;
        isGameOver = true;
    };

    vector<Ref<GameObject>> roomsPool = {
            scene->addGameObject(new GameObject(
                    "Column1",
                    new Model("/42run/Models/Column/Column.obj"),
                    new Texture("/42run/Models/Column/Column.png"),
                    {
                            new AABBCollider(glm::vec3(-0.75f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "TwoColumns1",
                    new Model("/42run/Models/TwoColumns/TwoColumns.obj"),
                    new Texture("/42run/Models/TwoColumns/TwoColumns.png"),
                    {
                            new AABBCollider(glm::vec3(-4.65f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(4.65f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "LeftTable1",
                    new Model("/42run/Models/LeftTable/LeftTable.obj"),
                    new Texture("/42run/Models/LeftTable/LeftTable.png"),
                    {
                            new AABBCollider(glm::vec3(-1.8f, -2.0f, 0.0f), glm::vec3(8.0f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "RightTable1",
                    new Model("/42run/Models/RightTable/RightTable.obj"),
                    new Texture("/42run/Models/RightTable/RightTable.png"),
                    {
                            new AABBCollider(glm::vec3(+1.8f, -2.0f, 0.0f), glm::vec3(8.0f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "TwoTables1",
                    new Model("/42run/Models/TwoTables/TwoTables.obj"),
                    new Texture("/42run/Models/TwoTables/TwoTables.png"),
                    {
                            new AABBCollider(glm::vec3(-5.5f, -2.0f, 0.0f), glm::vec3(4.1f, 1.8f, 1.2f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(+5.5f, -2.0f, 0.0f), glm::vec3(4.1f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "Tunel1",
                    new Model("/42run/Models/Tunel/Tunel.obj"),
                    new Texture("/42run/Models/Tunel/Tunel.png"),
                    {
                            new AABBCollider(glm::vec3(-5.5f, -1.75f, 0.0f), glm::vec3(4.1f, 4.0f, 4.1f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(+5.5f, -1.75f, 0.0f), glm::vec3(4.1f, 4.0f, 4.1f), true, true, collisionFunction),
                    }
            )),
    };

    vector<Ref<GameObject>> rooms = {
            scene->addGameObject(new GameObject(
                    "Column",
                    new Model("/42run/Models/Column/Column.obj"),
                    new Texture("/42run/Models/Column/Column.png"),
                    {
                            new AABBCollider(glm::vec3(-0.75f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "TwoColumns",
                    new Model("/42run/Models/TwoColumns/TwoColumns.obj"),
                    new Texture("/42run/Models/TwoColumns/TwoColumns.png"),
                    {
                            new AABBCollider(glm::vec3(-4.65f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(4.65f, -1.75f, 1.1f), glm::vec3(1.1f, 4.0f, 1.1f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "LeftTable",
                    new Model("/42run/Models/LeftTable/LeftTable.obj"),
                    new Texture("/42run/Models/LeftTable/LeftTable.png"),
                    {
                            new AABBCollider(glm::vec3(-1.8f, -2.0f, 0.0f), glm::vec3(8.0f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "RightTable",
                    new Model("/42run/Models/RightTable/RightTable.obj"),
                    new Texture("/42run/Models/RightTable/RightTable.png"),
                    {
                            new AABBCollider(glm::vec3(+1.8f, -2.0f, 0.0f), glm::vec3(8.0f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "TwoTables",
                    new Model("/42run/Models/TwoTables/TwoTables.obj"),
                    new Texture("/42run/Models/TwoTables/TwoTables.png"),
                    {
                            new AABBCollider(glm::vec3(-5.5f, -2.0f, 0.0f), glm::vec3(4.1f, 1.8f, 1.2f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(+5.5f, -2.0f, 0.0f), glm::vec3(4.1f, 1.8f, 1.2f), true, true, collisionFunction),
                    }
            )),
            scene->addGameObject(new GameObject(
                    "Tunel",
                    new Model("/42run/Models/Tunel/Tunel.obj"),
                    new Texture("/42run/Models/Tunel/Tunel.png"),
                    {
                            new AABBCollider(glm::vec3(-5.5f, -1.75f, 0.0f), glm::vec3(4.1f, 4.0f, 4.1f), true, true, collisionFunction),
                            new AABBCollider(glm::vec3(+5.5f, -1.75f, 0.0f), glm::vec3(4.1f, 4.0f, 4.1f), true, true, collisionFunction),
                    }
            )),
    };

    float t = 0;
    void onKeyEvent(Ref<Event>& event) override {
        if (isGameOver) {
            return;
        }

        float moveSpeed = 0.4f;
        if (event->getEventType() == EventType::KeyPress)
        {
            Ref<KeyPressEvent> keyPressEvent = dynamic_pointer_cast<KeyPressEvent>(event);
            if (keyPressEvent->key() == GLFW_KEY_A)
            {
                if (finn->transform()->position().x > -5.5f && finn->transform()->position().x < 5.5f) {
                    camera->transform()->translate(glm::vec3(-camera->transform()->model()[0]) * moveSpeed);
                }
                if (finn->transform()->position().x > -8.5f) {
                    finn->transform()->translate(glm::vec3(-moveSpeed, 0.0f, 0.0f));
                }
            }
            if (keyPressEvent->key() == GLFW_KEY_D)
            {
                if (finn->transform()->position().x > -5.5f && finn->transform()->position().x < 5.5f) {
                    camera->transform()->translate(glm::vec3(camera->transform()->model()[0]) * moveSpeed);
                }
                if (finn->transform()->position().x < 8.5f) {
                    finn->transform()->translate(glm::vec3(moveSpeed, 0.0f, 0.0f));
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

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> distrib;
    void start() override {
        gen = std::mt19937(rd());
        distrib = std::uniform_int_distribution<>(0, (int)roomsPool.size() - 1);
        std::shuffle(std::begin(rooms), std::end(rooms), std::default_random_engine(distrib(gen)));

        unsigned int size = rooms.size();
        vector<Ref<GameObject>> withEmptyRooms;
        for (int i = 0; i < size; i++) {
            withEmptyRooms.push_back(scene->addGameObject(new GameObject(
                    "Empty" + to_string(i),
                    new Model("/42run/Models/Empty/Empty.obj"),
                    new Texture("/42run/Models/Empty/Empty.png")
            )));
            withEmptyRooms.push_back(rooms[i]);
        }
        rooms = withEmptyRooms;

        finn->transform()->scale(glm::vec3(0.05f, 0.05f, 0.05f));
        finn->transform()->translate(glm::vec3(0.0f, 0.1f, 0.0f));
        finn->transform()->rotate(glm::vec3(0.0f, glm::pi<float>() + 0.9f, 0.0f));

        camera->transform()->translate(glm::vec3(0.0f, 9.0f, 9.0f));
        camera->transform()->rotate(glm::vec3(-0.5f, 0.0f, 0.0f));

        for (int i = 0; i < rooms.size(); i++) {
            rooms[i]->transform()->translate(glm::vec3(0.0f, 2.0f, (float)i * -7.8f));
        }
        for (auto & i : roomsPool) {
            i->transform()->translate(glm::vec3(0.0f, -100.0f, 100.0f));
        }
    }


    void update() override {
        if (isGameOver && isGrounded) {
            if (!isDead) {
                finn->transform()->rotate(glm::vec3(0.00f, 0.0f, 0.0f));
                finn->transform()->rotate(glm::vec3(1.5f, 0.0f, 0.0f));
                scene->addGameObject(new GameObject(
                        "GameOver",
                        new Text("Game Over", glm::vec3(600.0f, 700.0f, 0.0f), new Font("/42run/Textures/Font/BasicFont.bmp", 32, 32))
                ));
                isDead = true;
            }
            return;
        }

        if (!isGrounded) {
            finn->transform()->rotate(glm::vec3(-0.09f, 0.0f, 0.0f));
        } else {
            t += time->deltaTime();
            finn->transform()->rotate(glm::vec3(0.0f, -glm::sin(t * 5) / 5, 0.0f));
        }

        for (auto & room : rooms) {
            if (room->transform()->position().z < 7.8f) {
                room->transform()->translate(glm::vec3(0.0f, 0.0f, 0.1f));
            } else {
                if (room->name().find("Empty") == std::string::npos) {
                    room->transform()->position(glm::vec3(0.0f, -100.0f, -100.0f));
                    room.swap(roomsPool[distrib(gen)]);
                }
                room->transform()->position(glm::vec3(0.0f, 2.0f, -7.8 * (rooms.size() - 1)));
            }
        }
        distanceValue->text()->update(to_string((int)time->time()));
    }
};

int main()
{
    GameScene gameScene("Game Scene", 1600, 1200);
    gameScene.loop();
}