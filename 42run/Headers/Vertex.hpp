//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_VERTEX_HPP
#define GLITTER_VERTEX_HPP

#include "glm/glm.hpp"

namespace ft
{
    // Vertex Format
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 uv;
    };
}

#endif //GLITTER_VERTEX_HPP
