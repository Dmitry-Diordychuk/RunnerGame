//
// Created by ebona on 05.05.2022.
//

#ifndef INC_42RUN_DEBUG_HPP
#define INC_42RUN_DEBUG_HPP

#include "glm/glm.hpp"
#include <iostream>

namespace ft {
    using namespace std;

    class Debug {
    public:
        static void printVec4(glm::vec4 vec) {
            cout << endl;
            cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << endl;
        }

        static void printMat4(glm::mat4 mat) {
            cout << endl;
            cout << mat[0].x << " " << mat[0].y << " " << mat[0].z << " " << mat[0].w << endl;
            cout << mat[1].x << " " << mat[1].y << " " << mat[1].z << " " << mat[1].w << endl;
            cout << mat[2].x << " " << mat[2].y << " " << mat[2].z << " " << mat[2].w << endl;
            cout << mat[3].x << " " << mat[3].y << " " << mat[3].z << " " << mat[3].w << endl;
        }
    };

}

#endif //INC_42RUN_DEBUG_HPP
