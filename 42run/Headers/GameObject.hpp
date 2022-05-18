//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "Transform.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Scene.hpp"

#include <memory>
#include <utility>

class Scene;

namespace ft {
    class GameObject {
    private:
        const std::string m_name = "GameObject";

        std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
        std::shared_ptr<RigidBody> m_rigidBody = std::make_shared<RigidBody>(); // TODO: nullptr
        std::shared_ptr<Model> m_model = nullptr;
        std::shared_ptr<Texture> m_texture = nullptr;
        std::shared_ptr<Collider> m_collider = nullptr;

    public:
        explicit GameObject(std::string  name) : m_name(std::move(name)) {}
        GameObject(std::string name, Model* model, Texture* texture);
        GameObject(std::string name, Model* model, Texture* texture, ColliderType type);
        GameObject(std::string name, Collider* collider);

        std::string name() { return m_name; }
        std::shared_ptr<Transform> transform() const { return m_transform; }
        std::shared_ptr<Model> model() const { return m_model; }
        std::shared_ptr<Texture> texture() const { return m_texture; }
        std::shared_ptr<RigidBody> rigidBody() const { return m_rigidBody; }
        std::shared_ptr<Collider> collider() const { return m_collider; }

        void updatePhysics(float deltaTime, const std::shared_ptr<Scene>& scene) const;
    };
}

#endif // GAMEOBJECT_HPP
