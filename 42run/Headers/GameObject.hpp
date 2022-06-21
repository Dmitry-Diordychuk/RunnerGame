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
#include "Text.hpp"

#include <utility>


namespace ft {
    class Scene;
    class Collider;
    class Text;

    using namespace std;

    class GameObject {
    private:
        const string m_name = "GameObject";

        Ref<Transform> m_transform = make_shared<Transform>();
        Ref<RigidBody> m_rigidBody = make_shared<RigidBody>(); // TODO: nullptr
        Ref<Model> m_model = nullptr;
        Ref<Texture> m_texture = nullptr;
        vector<Ref<Collider>> m_colliders;
        Ref<Text> m_text = nullptr;

    public:
        explicit GameObject(string  name) : m_name(move(name)) {}
        GameObject::GameObject(string name, Model *model);
        GameObject(string name, Model* model, Texture* texture);
        GameObject(string name, Model* model, const vector<Collider*>& colliders);
        GameObject(string name, Model* model, Texture* texture, const vector<Collider*>& colliders);
        GameObject(string name, const vector<Collider*>& collider);
        GameObject::GameObject(string name, Text* text);

        string name() { return m_name; }
        Ref<Transform> transform() const { return m_transform; }
        Ref<Model> model() const { return m_model; }
        Ref<Texture> texture() const { return m_texture; }
        Ref<RigidBody> rigidBody() const { return m_rigidBody; }
        vector<Ref<Collider>> colliders() const { return m_colliders; }
        Ref<Text> text() const { return m_text; }

        void updatePhysics(float deltaTime, const Ref<Scene>& scene) const;
    };
}

#endif // GAMEOBJECT_HPP
