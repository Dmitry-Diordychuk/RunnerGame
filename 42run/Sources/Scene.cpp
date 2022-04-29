//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Scene.hpp"

std::shared_ptr<ft::GameObject> ft::Scene::addGameObject(std::shared_ptr<GameObject> object)
{
    std::cout << object->name() << " has been added to the scene." << std::endl;
    _objects.emplace(object->name(), object);
    return _objects[object->name()];
}