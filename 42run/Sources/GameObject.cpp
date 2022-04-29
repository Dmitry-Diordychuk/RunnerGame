//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "GameObject.hpp"

namespace ft {
    std::shared_ptr<MeshRenderer> ft::GameObject::meshRenderer() {
        return _meshRenderer;
    }

    GameObject::GameObject(const std::string name, const Mesh mesh)
        :   _name(name)
    {
        _meshRenderer->setMesh(mesh);
    }
}
