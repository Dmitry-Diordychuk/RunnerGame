//
// Created by Diordychuk Dmitry on 29.04.2022.
//

#include "Camera.hpp"

namespace ft {
    void Camera::init(int width, int height) { // TODO: view?
        glViewport(0, 0, width, height);

        m_projectionMatrix = glm::perspective(
                                glm::radians(45.0f),
                                (float)width/(float)height,
                                0.1f,
                                100.0f);
    }
}