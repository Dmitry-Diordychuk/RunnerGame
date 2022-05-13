//
// Created by Diordychuk Dmitry on 29.04.2022.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glitter.hpp"
#include "Transform.hpp"

#include <memory>


namespace ft {
    class Camera {
    private:
        std::shared_ptr<Transform> m_transform = std::make_shared<Transform>();
        glm::mat4 m_projectionMatrix;

    public:
        void init(int width, int height);

        std::shared_ptr<Transform> transform() const { return m_transform; }
        glm::mat4 projectionMatrix() const { return m_projectionMatrix; }
    };
}

#endif //CAMERA_HPP
