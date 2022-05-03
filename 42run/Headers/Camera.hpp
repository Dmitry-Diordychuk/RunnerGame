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
        std::shared_ptr<Transform> _transform = std::make_shared<Transform>();

    public:
        void init(int width, int height);

        std::shared_ptr<Transform> transform() { return _transform; }
    };
}

#endif //CAMERA_HPP
