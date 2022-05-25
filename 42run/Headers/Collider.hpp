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

namespace ft
{
    using namespace std;

    using Callback = function<void()>;

    enum ColliderType
    {
        AABB
    };

    class Collider
    {
    public:
        Collider(ColliderType type, Callback triggerCallback) : m_type(type), m_callback(move(triggerCallback)) {}
        virtual ~Collider() = default;

        bool isCollide(const Ref<Collider>& other);

        Ref<Transform> center() { return m_center; }

        Callback callback() { return m_callback; }

        Ref<Model> model() { return m_model; }


    protected:
        ColliderType m_type;
        Callback m_callback;
        Ref<Transform> m_center = make_shared<Transform>();
        Ref<Model> m_model = make_shared<Model>();

    };

    class AABBCollider : public Collider
    {
    public:
        AABBCollider(const glm::vec3& center, float halfX, float halfY, float halfZ, Callback triggerCallback = nullptr);

        bool testAABBAABB(const Ref<AABBCollider>& other) const;

    private:
        float m_halfX;
        float m_halfY;
        float m_halfZ;

    };
}

#endif //COLLIDER_HPP
