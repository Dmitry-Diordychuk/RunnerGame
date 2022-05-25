//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "Scene.hpp"

namespace ft {
    Ref<ft::GameObject> ft::Scene::addGameObject(GameObject *object) {
        Ref<GameObject> gameObject = Ref<GameObject>(object);
        cout << gameObject->name() << " has been added to the scene." << endl;
        _objects.emplace(gameObject->name(), gameObject);
        return _objects[gameObject->name()];
    }
}