//
// Created by ebona on 05.05.2022.
//

#ifndef INC_42RUN_DEBUG_HPP
#define INC_42RUN_DEBUG_HPP

#include "glm/glm.hpp"
#include <iostream>

class Debug
{
public:
    static void printVec4(glm::vec4 vec) {
        std::cout << std::endl;
        std::cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << std::endl;
    }

    static void printMat4(glm::mat4 mat) {
        std::cout << std::endl;
        std::cout << mat[0].x << " " << mat[0].y << " " << mat[0].z << " " << mat[0].w << std::endl;
        std::cout << mat[1].x << " " << mat[1].y << " " << mat[1].z << " " << mat[1].w << std::endl;
        std::cout << mat[2].x << " " << mat[2].y << " " << mat[2].z << " " << mat[2].w << std::endl;
        std::cout << mat[3].x << " " << mat[3].y << " " << mat[3].z << " " << mat[3].w << std::endl;
    }
};

#endif //INC_42RUN_DEBUG_HPP
