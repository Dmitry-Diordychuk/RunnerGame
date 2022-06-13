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

    GameObject::GameObject(string name, Model* model, const vector<Collider*>& colliders)
    : GameObject(move(name), model)
    {
        for (auto &collider : colliders) {
            if (collider->isInitialized()) {
                m_colliders.push_back(Ref<Collider>(collider));
                m_colliders.back()->gameObject(Ref<GameObject>(this));
                continue;
            }

            if (collider->type() == ColliderType::AABB) {
                glm::vec3 min = model->getMin();
                glm::vec3 max = model->getMax();
                glm::vec3 half = glm::vec3(glm::abs(max.x - min.x) / 2, glm::abs(max.y - min.y) / 2,
                                           glm::abs(max.z - min.z) / 2);
                m_colliders.push_back(make_shared<AABBCollider>(
                        transform()->position(),
                        half,
                        collider->isStatic(),
                        collider->isTrigger(),
                        nullptr
                ));
                m_colliders.back()->gameObject(Ref<GameObject>(this));
            }
        }
    }

    // TODO: тоже что выше
    // TODO: лямбда колайдера не работает
    GameObject::GameObject(string name, Model* model, Texture* texture, const vector<Collider*>& colliders)
    : GameObject(move(name), model, texture)
    {
        for (auto &collider : colliders) {
            if (collider->isInitialized()) {
                m_colliders.push_back(Ref<Collider>(collider));
                m_colliders.back()->gameObject(Ref<GameObject>(this));
                continue;
            }

            if (collider->type() == ColliderType::AABB) {
                glm::vec3 min = model->getMin();
                glm::vec3 max = model->getMax();
                glm::vec3 half = glm::vec3(glm::abs(max.x - min.x) / 2, glm::abs(max.y - min.y) / 2,
                                           glm::abs(max.z - min.z) / 2);
                m_colliders.push_back(make_shared<AABBCollider>(
                        transform()->position(),
                        half,
                        collider->isStatic(),
                        collider->isTrigger(),
                        nullptr
                ));
                m_colliders.back()->gameObject(Ref<GameObject>(this));
            }
        }
    }

    GameObject::GameObject(string name, const vector<Collider*>& colliders)
    : m_name(move(name))
    {
        for (auto &collider : colliders) {
            m_colliders.push_back(Ref<Collider>(collider));
            m_colliders.back()->gameObject(Ref<GameObject>(this));
        }
    }

    void GameObject::updatePhysics(float deltaTime, const Ref<Scene>& scene) const {
        if (rigidBody()->isPhysicsOn()) {
            rigidBody()->updateVelocity(deltaTime);

            glm::vec3 dp = rigidBody()->velocity() * deltaTime;
            transform()->translate(dp);
        }

        for (auto &thisCollider : this->colliders()) {
            if (thisCollider) {
                for (auto &other: *scene) {
                    if (this->m_name == other.second->m_name) {
                        continue;
                    }
                    if (thisCollider->isStatic()) {
                        continue;
                    }

                    if (this != other.second.get()) {
                        for (auto &otherCollider : other.second->colliders()) {
                            if (thisCollider->isCollide(otherCollider)) {
                                if (thisCollider->getCallback()) {
                                    thisCollider->getCallback()(thisCollider, otherCollider); // TODO: не работает
                                }
                                if (otherCollider->getCallback()) {
                                    otherCollider->getCallback()(thisCollider, otherCollider);
                                }

                                if (otherCollider->isTrigger()) {
                                    continue;
                                }

                                glm::vec3 resolvedPosition = thisCollider->resolveContact();
                                this->transform()->translate(resolvedPosition);
                                this->rigidBody()->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
                            }
                        }
                    }
                }
            }
        }
    }
}
