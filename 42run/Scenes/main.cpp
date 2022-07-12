//
// Created by ebona on 07.07.2022.
//

#include "Engine.hpp"

class TestScene : public ft::Engine {
    using Engine::Engine;
};

int main()
{
    TestScene testScene("Test", 800, 600);
    return 0;
}