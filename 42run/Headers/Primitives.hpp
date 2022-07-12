//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "Mesh.hpp"

namespace ft
{
    class Primitives
    {
    public:
        static Mesh triangle() {
            static const Mesh triangle = {
                    {
                    Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 0
                    Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 1
                    Vertex{glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 2
                    },
                    {
                            0, 1, 2
                    },
                    {}
            };
            return triangle;
        };

        static Mesh cube() {
            static const Mesh cube = {
                    {
                            Vertex{glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 0
                               Vertex{glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 1
                                  Vertex{glm::vec3(1.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 2
                                     Vertex{glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)},  // 3

                                        Vertex{glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
                                               glm::vec2(0.f, 0.f)}, // 4
                                           Vertex{glm::vec3(0.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f),
                                                  glm::vec2(0.f, 0.f)}, // 5
                            Vertex{glm::vec3(1.f, 1.f, 1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 6
                               Vertex{glm::vec3(1.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec2(0.f, 0.f)}, // 7
                    },
                    {
                            0, 1, 2, 0, 2, 3, // front square
                            4, 5, 6, 4, 6, 7, // back square

                            4, 5, 1, 4, 1, 0, // left
                            3, 2, 6, 3, 6, 7, // right

                            1, 5, 6, 1, 6, 2, // top
                            0, 4, 7, 0, 7, 3, // bottom
                    },
                    {}
            };
            return cube;
        }
    };
}

#endif //PRIMITIVES_HPP
