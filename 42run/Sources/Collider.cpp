//
// Created by ebona on 15.05.2022.
//

#include "Collider.hpp"

namespace ft
{
    bool Collider::isCollide(const Ref<Collider>& other) {
        bool result = false;

        if (this->m_type == AABB && other->m_type == AABB)
        {
            auto currentAABB = dynamic_cast<AABBCollider*>(this);
            auto otherAABB = dynamic_pointer_cast<AABBCollider>(other);

            result = currentAABB->testAABBAABB(otherAABB);
        }

        return result;
    }

    AABBCollider::AABBCollider(bool isStatic, Callback triggerCallback)
    : Collider(ColliderType::AABB, isStatic, move(triggerCallback)), m_halfX(0), m_halfY(0), m_halfZ(0)
    {
        m_isInitialized = false;
    }

    AABBCollider::AABBCollider(const glm::vec3 &center, float halfX, float halfY, float halfZ, bool isStatic, Callback triggerCallback)
    : Collider(ColliderType::AABB, isStatic, move(triggerCallback)), m_halfX(halfX), m_halfY(halfY), m_halfZ(halfZ)
    {
        m_center->translate(center);
        if (Consts::IS_COLLISION_DEBUG_ON)
        {
            m_model->loadBox(center, halfX, halfY, halfZ);
        }
    }

    bool AABBCollider::testAABBAABB(const Ref<AABBCollider>& other) const {
        if (glm::abs(this->m_center->position().x - other->m_center->position().x) > this->m_halfX + other->m_halfX) return false;
        if (glm::abs(this->m_center->position().y - other->m_center->position().y) > this->m_halfY + other->m_halfY) return false;
        if (glm::abs(this->m_center->position().z - other->m_center->position().z) > this->m_halfZ + other->m_halfZ) return false;
        return true;
    }
}