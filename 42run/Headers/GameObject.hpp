//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "Transform.hpp"
#include "Model.hpp"
#include "Texture.hpp"

#include <memory>
#include <utility>

namespace ft {
    class GameObject {
    private:
        const std::string m_name = "GameObject";

        std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
        std::shared_ptr<Model> m_model = nullptr;
        std::shared_ptr<Texture> m_texture = nullptr;

    public:
        explicit GameObject(std::string  name) : m_name(std::move(name)) {}
        GameObject(std::string name, Model* model, Texture* texture);

        std::string name() { return m_name; }
        std::shared_ptr<Transform> transform() const { return m_transform; }
        std::shared_ptr<Model> model() const { return m_model; }
        std::shared_ptr<Texture> texture() const { return m_texture; }


    };
}

#endif // GAMEOBJECT_HPP
