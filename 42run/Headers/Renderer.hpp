//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

// Local Headers
#include "glitter.hpp"

// System Headers
#include <iostream>

#include <memory>

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"


namespace ft {
    class Renderer {
    public:
        static void init(int width, int height);

        static void draw(const Shader& shader, const VertexArray& vertexArray, const ElementBuffer& indexBuffer);

        static void setClearColor(const glm::vec4& color);
        static void clear();

    };
}

#endif //RENDERER_HPP
