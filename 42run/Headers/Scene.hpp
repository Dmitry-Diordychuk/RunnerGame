//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_SCENE_HPP
#define GLITTER_SCENE_HPP

#include <map>

#include "GameObject.hpp"

namespace ft
{
    class Scene
    {
    private:
        std::map<std::string, std::shared_ptr<GameObject>> _objects;

    public:
        Scene() = default;

        std::shared_ptr<GameObject> addGameObject(std::shared_ptr<GameObject> object);
    };
}

#endif //GLITTER_SCENE_HPP
