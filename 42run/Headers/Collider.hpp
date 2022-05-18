//
// Created by ebona on 14.05.2022.
//

#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <glm/glm.hpp>
#include <utility>
#include <vector>
#include <functional>
#include <memory>

#include "Transform.hpp"
#include "Model.hpp"
#include "Consts.hpp"

namespace ft
{
    using Callback = std::function<void()>;

    enum ColliderType
    {
        AABB
    };

    class Collider
    {
    public:
        Collider(ColliderType type, Callback triggerCallback) : m_type(type), m_callback(std::move(triggerCallback)) {}
        virtual ~Collider() = default;

        bool isCollide(const std::shared_ptr<Collider>& other);

        Transform& center() { return m_center; }

        Callback callback() { return m_callback; }

        Model& model() { return m_model; }


    protected:
        ColliderType m_type;
        Callback m_callback;
        Transform m_center;
        Model m_model;

    };

    class AABBCollider : public Collider
    {
    public:
        AABBCollider(const glm::vec3& center, float halfX, float halfY, float halfZ, Callback triggerCallback = nullptr);

        bool testAABBAABB(const std::shared_ptr<AABBCollider>& other) const;

    private:
        float m_halfX;
        float m_halfY;
        float m_halfZ;

    };
}

#endif //COLLIDER_HPP
