//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_GAMEOBJECT_HPP
#define GLITTER_GAMEOBJECT_HPP

#include <glm/glm.hpp>

#include <string>

#include "MeshRenderer.hpp"

namespace ft {
    class GameObject {
    private:
        static const int _counter = 0;

        const std::string _name = "GameObject";

        glm::mat4 _transformMatrix = glm::mat4(1.f);
        glm::vec3 _position = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 _angle = glm::vec3(0.f, 0.f, 0.f);

        std::shared_ptr<MeshRenderer> _meshRenderer = std::make_shared<MeshRenderer>();

    public:
        explicit GameObject(const std::string name) : _name(name) {}
        GameObject(const std::string name, const Mesh mesh);

        std::string name() { return _name; }

        Mesh getMesh() { return _mesh; }

        std::shared_ptr<MeshRenderer> meshRenderer();
    };
}

#endif //GLITTER_GAMEOBJECT_HPP
