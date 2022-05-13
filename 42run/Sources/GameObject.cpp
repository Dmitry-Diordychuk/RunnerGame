//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "GameObject.hpp"

#include <utility>

namespace ft {
    GameObject::GameObject(std::string name, Model* model, Texture* texture)
        : m_name(std::move(name))
    {
        m_model = std::shared_ptr<Model>(model);
        m_texture = std::shared_ptr<Texture>(texture);
    }
}
