//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "GameObject.hpp"

#include <utility>

// TODO: unique name generator. Map pick wrong object if name not unique.

namespace ft {
    GameObject::GameObject(string name, Model *model, Texture *texture)
    : m_name(move(name))
    {
        m_model = Ref<Model>(model);
        m_texture = Ref<Texture>(texture);
    }

    GameObject::GameObject(string name, Model *model)
    : m_name(move(name))
    {
        m_model = Ref<Model>(model);
        m_texture = nullptr;
    }

    GameObject::GameObject(string name, Model* model, Collider* collider)
    : GameObject(move(name), model)
    {
        if (collider->isInitialized()) {
            m_collider = Ref<Collider>(collider);
            m_collider->gameObject(Ref<GameObject>(this));
            return;
        }

        if (collider->type() == ColliderType::AABB)
        {
            glm::vec3 min = model->getMin();
            glm::vec3 max = model->getMax();
            glm::vec3 half = glm::vec3(glm::abs(max.x - min.x) / 2, glm::abs(max.y - min.y) / 2, glm::abs(max.z - min.z) / 2);
            m_collider = make_shared<AABBCollider>(
                transform()->position(),
                half,
                collider->isStatic(),
                nullptr
            );
            m_collider->gameObject(Ref<GameObject>(this));
        }
    }

    GameObject::GameObject(string name, Model* model, Texture* texture, Collider* collider)
    : GameObject(move(name), model, texture)
    {
        if (collider->isInitialized()) {
            m_collider = Ref<Collider>(collider);
            m_collider->gameObject(Ref<GameObject>(this));
            return;
        }

        if (collider->type() == ColliderType::AABB)
        {
            glm::vec3 min = model->getMin();
            glm::vec3 max = model->getMax();
            glm::vec3 half = glm::vec3(glm::abs(max.x - min.x) / 2, glm::abs(max.y - min.y) / 2, glm::abs(max.z - min.z) / 2);
            m_collider = make_shared<AABBCollider>(
                transform()->position(),
                half,
                collider->isStatic(),
                nullptr
            );
            m_collider->gameObject(Ref<GameObject>(this));
        }
    }

    GameObject::GameObject(string name, Collider* collider)
    : m_name(move(name))
    {
        m_collider = Ref<Collider>(collider);
        m_collider->gameObject(Ref<GameObject>(this));
    }

    void GameObject::updatePhysics(float deltaTime, const Ref<Scene>& scene) const {
        if (rigidBody()->isPhysicsOn()) {
            rigidBody()->updateVelocity(deltaTime);

            glm::vec3 dp = rigidBody()->velocity() * deltaTime;
            transform()->translate(dp);
        }

        if (this->collider()) {
            for (auto &other: *scene) {
                if (this->m_name == other.second->m_name) {
                    continue;
                }
                if (this->collider()->isStatic()) {
                    continue;
                }

                if (this != other.second.get()) {
                    if (this->collider()->isCollide(other.second->collider())) {
                        if (this->collider()->getCallback()) {
                            this->collider()->getCallback()();
                        }
                        if (other.second->collider()->getCallback()) {
                            other.second->collider()->getCallback()();
                        }

                        glm::vec3 resolvedPosition = this->collider()->resolveContact();
                        this->transform()->translate(resolvedPosition);
                        this->rigidBody()->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
                    }
                }
            }
        }
    }
}
