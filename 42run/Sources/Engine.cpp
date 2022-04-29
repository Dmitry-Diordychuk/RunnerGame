//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Engine.hpp"

ft::Engine::Engine() {
    std::cout << "Engine started" << std::endl;
}

void ft::Engine::create(int screenWidth, int screenHeight, const std::string &name) {
    _name = name;

    screen->open(screenWidth, screenHeight, name);

    shader->init();
    shader->attach("basic.vert");
    shader->attach("basic.frag");
    //shader->attach("basic.geom");
    shader->link();
    shader->activate();
    std::cout << "Shader activated" << std::endl;

    start();

    while (screen->isOpen())
    {
        update();

        // screen->prepareGLToDraw();
        for (auto &it : *scene) {
            screen->drawMesh(it.second->getMesh());
        }

        screen->clear();

        screen->display();
    }
    screen->close();
}
