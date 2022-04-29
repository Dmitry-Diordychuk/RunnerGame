//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Engine.hpp"

ft::Engine::Engine() {}

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

        screen->clear();

        screen->display();
    }
    screen->close();
}
