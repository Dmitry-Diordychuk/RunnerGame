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
        _transformMatrix = glm::scale(_transformMatrix, s);
    }

    void Transform::rotate(const glm::vec3 &r) {
        _angle = _angle + r;

        _transformMatrix = glm::rotate(_transformMatrix, r.x, glm::vec3(1.0f, 0.0f, 0.0f));
        _transformMatrix = glm::rotate(_transformMatrix, r.y, glm::vec3(0.0f, 1.0f, 0.0f));
        _transformMatrix = glm::rotate(_transformMatrix, r.z, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    void Transform::rotate(const glm::vec3 &v, float rv)
    {
        _transformMatrix = glm::rotate(_transformMatrix, rv, v);
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

    GLfloat *Transform::inverseModel() const {
        GLfloat *v = new GLfloat[4 * 4];

        glm::vec3 _left = _transformMatrix[0];
        glm::vec3 _up = _transformMatrix[1];
        glm::vec3 _lookAt = _transformMatrix[2];

        v[0] = -static_cast<GLfloat>(_left.x);
        v[4] = -static_cast<GLfloat>(_left.y);
        v[8] = -static_cast<GLfloat>(_left.z);
        v[12] = static_cast<GLfloat>(glm::dot(_position, _left));

        v[1] = static_cast<GLfloat>(_up.x);
        v[5] = static_cast<GLfloat>(_up.y);
        v[9] = static_cast<GLfloat>(_up.z);
        v[13] = -static_cast<GLfloat>(glm::dot(_position, _up));

        v[2] = -static_cast<GLfloat>(_lookAt.x);
        v[6] = -static_cast<GLfloat>(_lookAt.y);
        v[10] = -static_cast<GLfloat>(_lookAt.z);
        v[14] = static_cast<GLfloat>(glm::dot(_position, _lookAt));

        v[3] = static_cast<GLfloat>(0.0f);
        v[7] = static_cast<GLfloat>(0.0f);
        v[11] = static_cast<GLfloat>(0.0f);
        v[15] = static_cast<GLfloat>(1.0f);

        return v;
    }

    GLfloat *Transform::model() const {
        GLfloat *m = new GLfloat[4 * 4];

        glm::vec3 _left = _transformMatrix[0];
        glm::vec3 _up = _transformMatrix[1];
        glm::vec3 _lookAt = _transformMatrix[2];

        m[0] = static_cast<GLfloat>(_left.x);
        m[4] = static_cast<GLfloat>(_up.x);
        m[8] = static_cast<GLfloat>(_lookAt.x);
        m[12] = static_cast<GLfloat>(_position.x);

        m[1] = static_cast<GLfloat>(_left.y);
        m[5] = static_cast<GLfloat>(_up.y);
        m[9] = static_cast<GLfloat>(_lookAt.y);
        m[13] = -static_cast<GLfloat>(_position.y);

        m[2] = static_cast<GLfloat>(_left.z);
        m[6] = static_cast<GLfloat>(_up.z);
        m[10] = static_cast<GLfloat>(_lookAt.z);
        m[14] = -static_cast<GLfloat>(_position.z);

        m[3] = static_cast<GLfloat>(0.0f);
        m[7] = static_cast<GLfloat>(0.0f);
        m[11] = static_cast<GLfloat>(0.0f);
        m[15] = static_cast<GLfloat>(1.0f);

        return m;
    }
}