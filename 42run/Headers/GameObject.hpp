//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "Transform.hpp"
#include "MeshRenderer.hpp"

#include <memory>

namespace ft {
    class GameObject {
    private:
        const std::string _name = "GameObject";

        std::shared_ptr<Transform> _transform = std::make_shared<Transform>();
        std::shared_ptr<MeshRenderer> _meshRenderer = std::make_shared<MeshRenderer>();

    public:
        explicit GameObject(const std::string name) : _name(name) {}
        GameObject(const std::string name, const Mesh mesh) : _name(name) {
            _meshRenderer->setMesh(std::make_shared<Mesh>(mesh));
        }

        std::string name() { return _name; }

        std::shared_ptr<MeshRenderer> meshRenderer() { return _meshRenderer; }
        std::shared_ptr<Transform> transform() { return _transform; }
    };
}

#endif // GAMEOBJECT_HPP
