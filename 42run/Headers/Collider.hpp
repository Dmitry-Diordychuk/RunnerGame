//
// Created by ebona on 14.05.2022.
//

#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>
#include <utility>
#include <vector>
#include <functional>

#include "Pointer.hpp"

#include "Transform.hpp"
#include "Model.hpp"
#include "Consts.hpp"

#include "GameObject.hpp"

// TODO: collision resolving bug

namespace ft
{
    class GameObject;

    using namespace std;

    using Callback = function<void()>;

    enum ColliderType
    {
        AABB
    };

    class Collider
    {
    public:
        Collider(ColliderType type, bool isStatic, Callback triggerCallback)
        : m_type(type), m_isStatic(isStatic), m_callback(move(triggerCallback))  {}
        virtual ~Collider() = default;

        bool isCollide(const Ref<Collider>& other);

        glm::vec3 center() { return m_center; }
        void center(glm::vec3 center) { m_center = center; }

        Callback getCallback() { return m_callback; }

        Ref<Model> model() { return m_model; }

        void gameObject(Ref<GameObject> gameObject) { m_gameObject = gameObject; }
        Ref<GameObject> gameObject() { return m_gameObject; }

        bool isInitialized() const { return m_isInitialized; };

        bool isStatic() const { return m_isStatic; };

        ColliderType type() const { return m_type; };

        virtual glm::vec3 resolveContact() { ASSERT(false); return {0.0f, 0.0f, 0.0f}; };

    protected:
        ColliderType m_type;
        Callback m_callback;
        glm::vec3 m_center = glm::vec3(0.0f, 0.0f, 0.0f);
        Ref<Model> m_model = make_shared<Model>();
        Ref<GameObject> m_gameObject = nullptr;

        bool m_isStatic;
        bool m_isInitialized = true;

    };

    class AABBCollider : public Collider
    {
    public:
        explicit AABBCollider(bool isStatic, Callback triggerCallback = nullptr);
        AABBCollider(const glm::vec3& center, const glm::vec3 &half, bool isStatic, Callback triggerCallback = nullptr);

        bool testAABBAABB(const Ref<AABBCollider>& other);

        glm::vec3 resolveContact() override;

    private:
        glm::vec3 m_half;
        glm::vec3 m_correction;

    };
}

#endif //COLLIDER_HPP
