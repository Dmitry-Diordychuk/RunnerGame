//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Engine.hpp"

#include <utility>

namespace ft {
    Engine::Engine(const string &name, int screenWidth, int screenHeight) {
        eventHandler->init(
            [this](Ref<Event> event) { onWindowEvent(event); },
            [this](Ref<Event> event) { onKeyEvent(event); }
        );
        window->open(WindowProps(name, screenWidth, screenHeight));
        camera->init(screenWidth, screenHeight);
        renderer->init(screenWidth, screenHeight, glm::vec4(0.1f, 0.2f, 0.3f, 1.0f));
        cout << "Engine started" << endl;
    }

    void ft::Engine::loop() {
        time->init();
        start();

        while (window->isOpen()) {
            renderer->clear();

            update();

            for (const auto& it : *scene) {
                Ref<GameObject> gameObject = it.second;

                gameObject->updatePhysics(time->deltaTime(), scene);

                renderer->draw(*it.second, *camera);
                if (Consts::IS_COLLISION_DEBUG_ON) {
                    renderer->drawCollider(*it.second, *camera);
                }
            }

            window->update();
            eventHandler->update(window->getProps().event);
            time->update();
        }
        window->close();
    }
}
