//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include <map>

#include "GameObject.hpp"
#include <iostream>

#include <memory>


namespace ft
{
    class Scene
    {
    private:
        std::map<std::string, std::shared_ptr<GameObject>> _objects;

    public:
        Scene() = default;

        std::shared_ptr<GameObject> addGameObject(std::shared_ptr<GameObject> object);

        std::map<std::string, std::shared_ptr<GameObject>>::iterator begin() { return _objects.begin(); }
        std::map<std::string, std::shared_ptr<GameObject>>::iterator end() { return _objects.end(); }
    };
}

#endif //SCENE_HPP
