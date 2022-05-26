//
// Created by Diordychuk Dmitry on 30.04.2022.
//

#include "Transform.hpp"

namespace ft
{
    void Transform::transform(const glm::mat4 &t) {
        m_transformMatrix = t * m_transformMatrix;

        for (auto& it : m_children)
        {
            it->m_transformMatrix = t * it->m_transformMatrix;
        }
    }

    void Transform::transformRelativePoint(const glm::vec3 &point, const glm::mat4 &transform) {
//        // translate object in new coordinate system connected with point
//        m_transformMatrix = glm::translate(m_transformMatrix, m_position - point);
//        // transform object in the new coordinate system
//        m_transformMatrix = transform * m_transformMatrix;
//        // translate object back in self connected coordinate system
//        m_position = m_transformMatrix[3] + glm::vec4(point, 1.0f);
//        m_transformMatrix = glm::translate(m_transformMatrix, -(glm::vec3(m_transformMatrix[3])));
    }

    void Transform::translate(const glm::vec3 &dv) {
        m_position = m_position + dv;

        for (auto& it : m_children)
        {
            it->m_position = it->m_position + dv;
        }
    }

    void Transform::scale(const glm::vec3 &s) {
        m_scale = s;

        for (auto& it : m_children)
        {
            it->m_scale = s;
        }
    }

    void Transform::rotate(const glm::vec3 &r) {
        m_angle = m_angle + r;

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation = glm::rotate(rotation, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, r.z, glm::vec3(0.0f, 0.0f, 1.0f));

        transform(rotation);

        for (auto& it : m_children)
        {
            it->m_angle = it->m_angle + r;
            it->transform(rotation);
        }
    }

    void Transform::rotate(const glm::vec3 &v, float rv) {
        glm::vec3 normalizedV = glm::normalize(v);

        m_transformMatrix = glm::rotate(m_transformMatrix, rv, normalizedV);

        for (auto& it : m_children)
        {
            it->m_transformMatrix = glm::rotate(it->m_transformMatrix, rv, normalizedV);
        }
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &r) {
//        m_angle = m_angle + r;
//
//        transformRelativePoint(s, glm::rotate(m_transformMatrix, r.x, s));
//        transformRelativePoint(s, glm::rotate(m_transformMatrix, r.y, s));
//        transformRelativePoint(s, glm::rotate(m_transformMatrix, r.z, s));
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &v, float r) {
        //transformRelativePoint(s, glm::rotate(m_transformMatrix, r, v));
    }

    glm::mat4 Transform::inverseModel() {
        glm::mat4 translation = glm::mat4(1.0f);
        translation[3][0] = m_position.x;
        translation[3][1] = m_position.y;
        translation[3][2] = m_position.z;

        glm::mat4 scale = glm::mat4(1.0f);
        scale[0][0] = m_scale.x;
        scale[1][1] = m_scale.y;
        scale[2][2] = m_scale.z;

        return glm::inverse(translation * m_transformMatrix * scale);
    }

    glm::mat4 Transform::model() {
        glm::mat4 translation = glm::mat4(1.0f);
        translation[3][0] = m_position.x;
        translation[3][1] = m_position.y;
        translation[3][2] = m_position.z;

        glm::mat4 scale = glm::mat4(1.0f);
        scale[0][0] = m_scale.x;
        scale[1][1] = m_scale.y;
        scale[2][2] = m_scale.z;

        return translation * m_transformMatrix * scale;
    }

    void Transform::addChild(const Ref<Transform>& transform) {
        m_children.push_back(transform);
    }
}