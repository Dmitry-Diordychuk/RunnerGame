//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Engine.hpp"

namespace ft {
    Engine::Engine(const std::string &name, int screenWidth, int screenHeight) {
        window->open(WindowProps(name, screenWidth, screenHeight));
        camera->init(screenWidth, screenHeight);
        renderer->setClearColor(glm::vec4(0.1f, 0.2f, 0.3f, 1.0f));
        std::cout << "Engine started" << std::endl;
    }

    void ft::Engine::loop() {
        start();

        while (window->isOpen()) {
            renderer->clear();

            update();

            for (auto &it : *scene) {
                renderer->draw(it.second, camera);
            }

            window->update();
        }
        window->close();
    }
}
