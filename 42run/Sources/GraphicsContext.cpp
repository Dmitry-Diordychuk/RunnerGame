//
// Created by ebona on 02.05.2022.
//

#include "GraphicsContext.hpp"

namespace ft{

    std::unique_ptr<GraphicsContext> GraphicsContext::create(GLFWwindow *windowHandler) {
        return std::make_unique<GraphicsContext>(windowHandler);
    }

    void GraphicsContext::init() {
        glfwMakeContextCurrent(m_windowHandler);
        if (!gladLoadGL()) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        std::cerr << "OpenGL " << glGetString(GL_VERSION) << std::endl;
    }

    void GraphicsContext::swapBuffers() {
        glfwSwapBuffers(m_windowHandler);
    }
}