//
// Created by ebona on 15.05.2022.
//

#include "Collider.hpp"

namespace ft
{
    bool Collider::isCollide(const Ref<Collider>& other) {
        if (other == nullptr) return false;

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
    : Collider(ColliderType::AABB, isStatic, move(triggerCallback)),
        m_half(0.0f, 0.0f, 0.0f),
        m_correction(0.0f, 0.0f, 0.0f)
    {
        m_center = glm::vec3(0.0f, 0.0f, 0.0f);
        m_isInitialized = false;
    }

    AABBCollider::AABBCollider(const glm::vec3 &center, const glm::vec3 &half, bool isStatic, Callback triggerCallback)
    : Collider(ColliderType::AABB, isStatic, move(triggerCallback)),
        m_half(half),
        m_correction(0.0f, 0.0f, 0.0f)
    {
        m_center = center;
        m_center.y = m_center.y + half.y;
        if (Consts::IS_COLLISION_DEBUG_ON)
        {
            m_model->loadBox(m_center, m_half.x, m_half.y, m_half.z);
        }
    }

    bool AABBCollider::testAABBAABB(const Ref<AABBCollider>& other) {
        glm::mat4 thisModel = this->gameObject()->transform()->model();
        glm::mat4 otherModel = other->gameObject()->transform()->model();

        glm::vec3 thisPos = thisModel * glm::vec4(this->center(), 1.0f);
        glm::vec3 otherPos = otherModel * glm::vec4(other->center(), 1.0f);

        float subX = thisPos.x - otherPos.x;
        float subY = thisPos.y - otherPos.y;
        float subZ = thisPos.z - otherPos.z;

        glm::vec3 thisHalf = glm::vec3(this->m_half.x * thisModel[0][0], this->m_half.y * thisModel[1][1], this->m_half.z * thisModel[2][2]);
        glm::vec3 otherHalf = glm::vec3(other->m_half.x * otherModel[0][0], other->m_half.y * otherModel[1][1], other->m_half.z * otherModel[2][2]);

        float absSubX = glm::abs(subX);
        float absSubY = glm::abs(subY);
        float absSubZ = glm::abs(subZ);

        if (absSubX > thisHalf.x + otherHalf.x) {
            return false;
        }
        if (absSubY > thisHalf.y + otherHalf.y) {
            return false;
        }
        if (absSubZ > thisHalf.z + otherHalf.z) {
            return false;
        }

        //cout << "X " << absSubX << " Y " << absSubY << " Z " << absSubZ << endl;
        if (absSubX > absSubY && absSubX > absSubZ) {
            m_correction.x = glm::sign(subX) * (thisHalf.x + otherHalf.x - absSubX);
            m_correction.y = 0.0f;
            m_correction.z = 0.0f;
        }
        if (absSubY > absSubX && absSubY > absSubZ) {
            m_correction.x = 0.0f;
            m_correction.y = glm::sign(subY) * (thisHalf.y + otherHalf.y - absSubY);
            m_correction.z = 0.0f;
        }
        if (absSubZ > absSubX && absSubZ > absSubY) {
            m_correction.x = 0.0f;
            m_correction.y = 0.0f;
            m_correction.z = glm::sign(subZ) * (thisHalf.z + otherHalf.z - absSubZ);
        }
        return true;
    }

    glm::vec3 AABBCollider::resolveContact() {
        return m_correction;
    }
}