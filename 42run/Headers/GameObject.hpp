//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

#include "Pointer.hpp"

#include "Transform.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Scene.hpp"

#include <utility>

class Scene;
class Collider;

namespace ft {
    using namespace std;

    class GameObject {
    private:
        const string m_name = "GameObject";

        Ref<Transform> m_transform = make_shared<Transform>();
        Ref<RigidBody> m_rigidBody = make_shared<RigidBody>(); // TODO: nullptr
        Ref<Model> m_model = nullptr;
        Ref<Texture> m_texture = nullptr;
        Ref<Collider> m_collider = nullptr;

    public:
        explicit GameObject(string  name) : m_name(move(name)) {}
        GameObject::GameObject(string name, Model *model);
        GameObject(string name, Model* model, Texture* texture);
        GameObject(string name, Model* model, Collider* collider);
        GameObject(string name, Model* model, Texture* texture, Collider* collider);
        GameObject(string name, Collider* collider);

        string name() { return m_name; }
        Ref<Transform> transform() const { return m_transform; }
        Ref<Model> model() const { return m_model; }
        Ref<Texture> texture() const { return m_texture; }
        Ref<RigidBody> rigidBody() const { return m_rigidBody; }
        Ref<Collider> collider() const { return m_collider; }

        void updatePhysics(float deltaTime, const Ref<Scene>& scene) const;
    };
}

#endif // GAMEOBJECT_HPP
