//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Scene.hpp"

std::shared_ptr<ft::GameObject> ft::Scene::addGameObject(GameObject* object)
{
    std::shared_ptr<GameObject> gameObject = std::shared_ptr<GameObject>(object);
    std::cout << gameObject->name() << " has been added to the scene." << std::endl;
    _objects.emplace(gameObject->name(), gameObject);
    return _objects[gameObject->name()];
}