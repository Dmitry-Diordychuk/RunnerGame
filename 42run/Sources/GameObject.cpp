//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "GameObject.hpp"

#include <utility>

namespace ft {
    GameObject::GameObject(std::string name, Model *model, Texture *texture) : m_name(std::move(name)) {
        m_model = std::shared_ptr<Model>(model);
        m_texture = std::shared_ptr<Texture>(texture);
    }

    GameObject::GameObject(std::string name, Model* model, Texture* texture, ColliderType type)
        : GameObject(std::move(name), model, texture)
    {
        if (type == ColliderType::AABB)
        {
            glm::vec3 min = model->getMin();
            glm::vec3 max = model->getMax();
            m_collider = std::make_shared<AABBCollider>(
                transform()->position(),
                glm::abs(max.x - min.x) / 2,
                glm::abs(max.y - min.y) / 2,
                glm::abs(max.z - min.z) / 2,
                nullptr
            );
        }
    }

    GameObject::GameObject(std::string name, Collider* collider) : m_name(std::move(name)) {
        m_collider = std::shared_ptr<Collider>(collider);
    }

    void GameObject::updatePhysics(float deltaTime, const std::shared_ptr<Scene>& scene) const {
        if (rigidBody()->isPhysicsOn())
        {
            rigidBody()->updateVelocity(deltaTime);

            glm::vec3 dp = rigidBody()->velocity() * deltaTime;
            transform()->translate(dp);

            if (collider())
            {
                collider()->center().translate(dp);
            }
        }

        for (auto& other : *scene)
        {
            if (this != other.second.get())
            {
                if (this->collider()->isCollide(other.second->collider()))
                {
                    this->collider()->callback();
                    other.second->collider()->callback();
                }
            }
        }
    }
}
