//
// Created by ebona on 03.05.2022.
//

#include "GlError.hpp"

namespace ft
{
    void GLClearError() {
        while (glGetError() != GL_NO_ERROR);
    }

    bool GLLogCall(const char *function, const char *file, int line) {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << " " << line << std::endl;
            return false;
        }
        return true;
    }

    void GLLogCall()
    {
        while (GLenum error = glGetError()) {
            std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
        }
    }
}