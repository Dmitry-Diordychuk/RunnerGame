//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>

#include "GameObject.hpp"
#include <iostream>

#include "Pointer.hpp"

namespace ft
{
    using namespace std;

    class GameObject;

    class Scene
    {
    private:
        map<string, Ref<GameObject>> _objects;

    public:
        Scene() = default;

        Ref<GameObject> addGameObject(GameObject* object);

        map<string, Ref<GameObject>>::iterator begin() { return _objects.begin(); }
        map<string, Ref<GameObject>>::iterator end() { return _objects.end(); }
    };
}

#endif //SCENE_HPP
