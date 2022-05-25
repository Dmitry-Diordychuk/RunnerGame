//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "GameObject.hpp"

#include <utility>

namespace ft {
    GameObject::GameObject(string name, Model *model, Texture *texture) : m_name(move(name)) {
        m_model = Ref<Model>(model);
        m_texture = Ref<Texture>(texture);
    }

    GameObject::GameObject(string name, Model* model, Texture* texture, ColliderType type)
        : GameObject(move(name), model, texture)
    {
        if (type == ColliderType::AABB)
        {
            glm::vec3 min = model->getMin();
            glm::vec3 max = model->getMax();
            m_collider = make_shared<AABBCollider>(
                transform()->position(),
                glm::abs(max.x - min.x) / 2,
                glm::abs(max.y - min.y) / 2,
                glm::abs(max.z - min.z) / 2,
                nullptr
            );
        }
    }

    GameObject::GameObject(string name, Collider* collider) : m_name(move(name)) {
        m_collider = Ref<Collider>(collider);
    }

    void GameObject::updatePhysics(float deltaTime, const Ref<Scene>& scene) const {
        if (rigidBody()->isPhysicsOn())
        {
            rigidBody()->updateVelocity(deltaTime);

            glm::vec3 dp = rigidBody()->velocity() * deltaTime;
            transform()->translate(dp);

            if (collider())
            {
                collider()->center()->translate(dp);
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
