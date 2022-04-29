//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Engine.hpp"

using namespace ft;

class Lesson2 : public Engine
{
private:
    //double rotationSpeed = 1;
    std::shared_ptr<GameObject> cube = scene->addGameObject(
        std::make_shared<GameObject>(GameObject("cube", Primitives::cube()))
    );

public:
    Lesson2() = default;

    void start() override {
    }

    void update() override {

    }
};

int main()
{
    Lesson2 lesson2;
    lesson2.create();
}