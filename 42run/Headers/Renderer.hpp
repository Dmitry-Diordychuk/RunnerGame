//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

// Local Headers
#include "glitter.hpp"

// System Headers
#include <exception>
#include <iostream>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

#include <memory>


namespace ft {
    class Renderer {
    public:
        static void draw(const std::shared_ptr<GameObject>& object, const std::shared_ptr<Camera>& camera);

        static void setClearColor(const glm::vec4& color);
        static void clear();

    };
}

#endif //RENDERER_HPP
