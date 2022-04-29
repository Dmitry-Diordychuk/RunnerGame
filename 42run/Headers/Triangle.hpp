//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_TRIANGLE_HPP
#define GLITTER_TRIANGLE_HPP

#include "glm/glm.hpp"

namespace ft {
    class Triangle {
    private:
        // color
        glm::vec4 _points[3];
        // glm::vec3 _normal;

    public:
        Triangle() = default;

        Triangle(const Triangle &triangle);

        Triangle(const glm::vec4 &p1, const glm::vec4 &p2, const glm::vec4 &p3);

        Triangle &operator=(const Triangle &) = default;

        const glm::vec4 &operator[](int i) const;

    };
}

#endif //GLITTER_TRIANGLE_HPP
