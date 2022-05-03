//
// Created by ebona on 03.05.2022.
//

#ifndef GLERROR_HPP
#define GLERROR_HPP

#include <iostream>

#include "glad/glad.h"

namespace ft {
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

    void GLClearError();

    bool GLLogCall(const char *function, const char *file, int line);

    void GLLogCall();
}

#endif //GLERROR_HPP
