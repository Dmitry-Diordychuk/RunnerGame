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
            string errorStr;
            switch (error)
            {
                case GL_INVALID_ENUM:                  errorStr = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 errorStr = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             errorStr = "INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                errorStr = "STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               errorStr = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 errorStr = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: errorStr = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            cout << "[OpenGL Error] (" << errorStr << ")" << function << " " << file << " " << line << endl;
            return false;
        }
        return true;
    }

    void GLLogCall()
    {
        while (GLenum error = glGetError()) {
            cout << "[OpenGL Error] (" << error << ")" << endl;
        }
    }
}