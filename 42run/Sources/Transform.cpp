//
// Created by Diordychuk Dmitry on 30.04.2022.
//

#include "Transform.hpp"

namespace ft
{
    void Transform::transform(const glm::mat4 &t) {
        _transformMatrix = t * _transformMatrix;
    }

    void Transform::transformRelativePoint(const glm::vec3 &point, const glm::mat4 &transform) {
        // translate object in new coordinate system connected with point
        _transformMatrix = glm::translate(_transformMatrix, _position - point);
        // transform object in the new coordinate system
        _transformMatrix = transform * _transformMatrix;
        // translate object back in self connected coordinate system
        _position = _transformMatrix[3] + glm::vec4(point, 1.0f);
        _transformMatrix = glm::translate(_transformMatrix, -(glm::vec3(_transformMatrix[3])));
    }

    void Transform::translate(const glm::vec3 &dv) {
        _position = _position + dv;
    }

    void Transform::scale(const glm::vec3 &s) {
        _scale = s;
    }

    void Transform::rotate(const glm::vec3 &r) {
        _angle = _angle + r;

        glm::mat4 rotation = glm::mat4(1.0f);
        rotation = glm::rotate(rotation, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, r.z, glm::vec3(0.0f, 0.0f, 1.0f));
        transform(rotation);
    }

    void Transform::rotate(const glm::vec3 &v, float rv) {
        _transformMatrix = glm::rotate(_transformMatrix, rv, glm::normalize(v));
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &r) {
        _angle = _angle + r;

        transformRelativePoint(s, glm::rotate(_transformMatrix, r.x, s));
        transformRelativePoint(s, glm::rotate(_transformMatrix, r.y, s));
        transformRelativePoint(s, glm::rotate(_transformMatrix, r.z, s));
    }

    void Transform::rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &v, float r) {
        transformRelativePoint(s, glm::rotate(_transformMatrix, r, v));
    }

    glm::mat4 Transform::inverseModel() {
        glm::mat4 translation = glm::mat4(1.0f);
        translation[3][0] = _position.x;
        translation[3][1] = _position.y;
        translation[3][2] = _position.z;

        glm::mat4 scale = glm::mat4(1.0f);
        scale[0][0] = _scale.x;
        scale[1][1] = _scale.y;
        scale[2][2] = _scale.z;

        return glm::inverse(translation * _transformMatrix * scale);
    }

    glm::mat4 Transform::model() {
        glm::mat4 translation = glm::mat4(1.0f);
        translation[3][0] = _position.x;
        translation[3][1] = _position.y;
        translation[3][2] = _position.z;

        glm::mat4 scale = glm::mat4(1.0f);
        scale[0][0] = _scale.x;
        scale[1][1] = _scale.y;
        scale[2][2] = _scale.z;

        return translation * _transformMatrix * scale;
    }
}