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

    GameObject::GameObject(string name, Model* model, Texture* texture, Collider* collider)
        : GameObject(move(name), model, texture)
    {
        if (collider->isInitialized()) {
            m_collider = Ref<Collider>(collider);
            return;
        }

        if (collider->type() == ColliderType::AABB)
        {
            glm::vec3 min = model->getMin();
            glm::vec3 max = model->getMax();
            m_collider = make_shared<AABBCollider>(
                transform()->position(),
                glm::abs(max.x - min.x) / 2,
                glm::abs(max.y - min.y) / 2,
                glm::abs(max.z - min.z) / 2,
                collider->isStatic(),
                nullptr
            );
            m_transform->addChild(m_collider->center());
        }
    }

    GameObject::GameObject(string name, Collider* collider) : m_name(move(name)) {
        m_collider = Ref<Collider>(collider);
        m_transform->addChild(m_collider->center());
    }

    void GameObject::updatePhysics(float deltaTime, const Ref<Scene>& scene) const {
        if (rigidBody()->isPhysicsOn())
        {
            rigidBody()->updateVelocity(deltaTime);

            glm::vec3 dp = rigidBody()->velocity() * deltaTime;
            transform()->translate(dp);
        }

        if (this->collider()) {
            for (auto &other: *scene) {
                if (this != other.second.get()) {
                    if (this->collider()->isCollide(other.second->collider())) {
                        if (this->collider()->getCallback()) {
                            this->collider()->getCallback()();
                        }
                        if (other.second->collider()->getCallback()) {
                            other.second->collider()->getCallback()();
                        }

                        if (!this->collider()->isStatic())
                        {
                            this->transform()->translate(this->collider()->getPositionCorrection());
                            //rigidBody()->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
                            //rigidBody()->setAcceleration(glm::vec3(0.0f, 0.0f, 0.0f));
                        }
                    }
                }
            }
        }
    }
}
