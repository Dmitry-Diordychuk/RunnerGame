//
// Created by Diordychuk Dmitry on 30.04.2022.
//

#include "Transform.hpp"

namespace ft
{
    void Transform::transform(const glm::mat4 &t) {
        m_rotationMatrix = t * m_rotationMatrix;

        for (auto& it : m_children)
        {
            it->transform(t);
        }
    }

    void Transform::transformRelativePoint(const glm::vec3 &point, const glm::mat4 &transform) {
//        // translate object in new coordinate system connected with point
//        m_rotationMatrix = glm::translate(m_rotationMatrix, m_position - point);
//        // transform object in the new coordinate system
//        m_rotationMatrix = transform * m_rotationMatrix;
//        // translate object back in self connected coordinate system
//        m_position = m_rotationMatrix[3] + glm::vec4(point, 1.0f);
//        m_rotationMatrix = glm::translate(m_rotationMatrix, -(glm::vec3(m_rotationMatrix[3])));
    }

    void Transform::translate(const glm::vec3 &dv) {
        m_position = m_position + dv;

        for (auto& it : m_children)
        {
            it->translate(dv);
        }
    }

    void Transform::scale(const glm::vec3 &s) {
        m_scale = s;

        for (auto& it : m_children)
        {
            it->scale(s);
        }
    }

    void Transform::rotate(const glm::vec3 &r) {
        if (!m_isRotatable) {
            return;
        }

        m_angle = m_angle + r;

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation = glm::rotate(rotation, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, r.z, glm::vec3(0.0f, 0.0f, 1.0f));

        transform(rotation);

        for (auto& it : m_children)
        {
            it->rotate(r);
        }
    }

    void Transform::rotate(const glm::vec3 &v, float rv) {
        if (!m_isRotatable) {
            return;
        }

        glm::vec3 normalizedV = glm::normalize(v);

        m_rotationMatrix = glm::rotate(m_rotationMatrix, rv, normalizedV);

        for (auto& it : m_children)
        {
            it->rotate(v, rv);
        }
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &r) {
        if (!m_isRotatable) {
            return;
        }

//        m_angle = m_angle + r;
//
//        transformRelativePoint(s, glm::rotate(m_rotationMatrix, r.x, s));
//        transformRelativePoint(s, glm::rotate(m_rotationMatrix, r.y, s));
//        transformRelativePoint(s, glm::rotate(m_rotationMatrix, r.z, s));
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &v, float r) {
        if (!m_isRotatable) {
            return;
        }

        //transformRelativePoint(s, glm::rotate(m_rotationMatrix, r, v));
    }

    glm::mat4 Transform::inverseModel() {
        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix[3][0] = m_position.x;
        translationMatrix[3][1] = m_position.y;
        translationMatrix[3][2] = m_position.z;

        glm::mat4 scaleMatrix = glm::mat4(1.0f);
        scaleMatrix[0][0] = m_scale.x;
        scaleMatrix[1][1] = m_scale.y;
        scaleMatrix[2][2] = m_scale.z;

        return glm::inverse(translationMatrix * m_rotationMatrix * scaleMatrix);
    }

    glm::mat4 Transform::model() {
        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix[3][0] = m_position.x;
        translationMatrix[3][1] = m_position.y;
        translationMatrix[3][2] = m_position.z;

        glm::mat4 scaleMatrix = glm::mat4(1.0f);
        scaleMatrix[0][0] = m_scale.x;
        scaleMatrix[1][1] = m_scale.y;
        scaleMatrix[2][2] = m_scale.z;

        return translationMatrix * m_rotationMatrix * scaleMatrix;
    }

    glm::mat4 Transform::modelWithoutRotation() const {
        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix[3][0] = m_position.x;
        translationMatrix[3][1] = m_position.y;
        translationMatrix[3][2] = m_position.z;

        glm::mat4 scaleMatrix = glm::mat4(1.0f);
        scaleMatrix[0][0] = m_scale.x;
        scaleMatrix[1][1] = m_scale.y;
        scaleMatrix[2][2] = m_scale.z;

        return translationMatrix * scaleMatrix;
    }

    void Transform::addChild(const Ref<Transform>& transform) {
        m_children.push_back(transform);
    }
}