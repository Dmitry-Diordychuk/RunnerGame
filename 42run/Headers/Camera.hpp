//
// Created by Diordychuk Dmitry on 29.04.2022.
//

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glitter.hpp"
#include "Transform.hpp"

#include "Pointer.hpp"


namespace ft {
    using namespace std;

    class Camera {
    private:
        Ref<Transform> m_transform = make_shared<Transform>();
        glm::mat4 m_projectionMatrix;

    public:
        void init(int width, int height);

        Ref<Transform> transform() const { return m_transform; }
        glm::mat4 projectionMatrix() const { return m_projectionMatrix; }
    };
}

#endif //CAMERA_HPP
