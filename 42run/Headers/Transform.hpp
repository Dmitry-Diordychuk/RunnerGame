//
// Created by Diordychuk Dmitry on 30.04.2022.
//

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#include "Pointer.hpp"


namespace ft {
    class Transform {
    private:
        bool m_isRotatable = true;

        glm::mat4 m_rotationMatrix = glm::mat4(1.0f);

        glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 m_angle = glm::vec3(0.0f, 0.0f, 0.0f);

        vector<Ref<Transform>> m_children;

    public:
        void isRotatable(bool isRotatable) { m_isRotatable = isRotatable; }

        glm::vec3 position() const { return m_position; }
        void position(glm::vec3 position) { m_position = position; }

        glm::vec3 angle() const { return m_angle; }

        void transform(const glm::mat4 &t);

        void transformRelativePoint(const glm::vec3 &point, const glm::mat4 &transform);

        void translate(const glm::vec3 &dv);

        void scale(const glm::vec3 &s);

        void rotate(const glm::vec3 &r);

        void rotate(const glm::vec3 &v, float rv);

        void rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &r);

        void rotateRelativePoint(const glm::vec3 &s, const glm::vec3 &v, float r);

        glm::mat4 inverseModel();

        glm::mat4 model();

        void addChild(const Ref<Transform>&);
    };
}

#endif //TRANSFORM_HPP
