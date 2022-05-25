//
// Created by ebona on 02.05.2022.
//

#ifndef GRAPHICSCONTEXT_HPP
#define GRAPHICSCONTEXT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <stdexcept>
#include <iostream>

#include "Pointer.hpp"

namespace ft {
    class GraphicsContext {
    private:
        GLFWwindow *m_windowHandler;

    public:
        explicit GraphicsContext(GLFWwindow *windowHandler) : m_windowHandler(windowHandler) {}

        static Scope<GraphicsContext> create(GLFWwindow *windowHandler);
        void init();
        void swapBuffers();

    };
}

#endif //GRAPHICSCONTEXT_HPP
