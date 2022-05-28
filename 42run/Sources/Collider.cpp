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

    bool AABBCollider::testAABBAABB(const Ref<AABBCollider>& other) {
        bool result = true;
        float subX = this->m_center->position().x - other->m_center->position().x;
        float subY = this->m_center->position().y - other->m_center->position().y;
        float subZ = this->m_center->position().z - other->m_center->position().z;

        m_correctionX = -glm::sign(subX) * (this->m_halfX + other->m_halfX - glm::abs(subX));
        m_correctionY = -glm::sign(subY) * (this->m_halfY + other->m_halfY - glm::abs(subY));
        m_correctionZ = -glm::sign(subZ) * (this->m_halfZ + other->m_halfZ - glm::abs(subZ));

        if (glm::abs(subX) > this->m_halfX + other->m_halfX) {
            m_correctionX = 0.0f;
            result = false;
        }
        if (glm::abs(subY) > this->m_halfY + other->m_halfY) {
            m_correctionY = 0.0f;
            result = false;
        }
        if (glm::abs(subZ) > this->m_halfZ + other->m_halfZ) {
            m_correctionZ = 0.0f;
            result = false;
        }

        if (glm::abs(m_correctionX) < glm::abs(m_correctionY)) {
            m_correctionY = 0.0f;
            if (glm::abs(m_correctionX) > glm::abs(m_correctionZ)) {
                m_correctionZ = 0.0f;
            } else {
                m_correctionX = 0.0f;
            }
        } else {
            m_correctionX = 0.0f;
            if (glm::abs(m_correctionY) > glm::abs(m_correctionZ)) {
                m_correctionZ = 0.0f;
            } else {
                m_correctionY = 0.0f;
            }
        }

        return result;
    }

    glm::vec3 AABBCollider::getPositionCorrection() {
        return {-m_correctionX, -m_correctionY, -m_correctionZ};
    }
}