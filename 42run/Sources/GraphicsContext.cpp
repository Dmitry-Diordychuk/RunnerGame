//
// Created by ebona on 02.05.2022.
//

#include "GraphicsContext.hpp"

namespace ft{

    Scope<GraphicsContext> GraphicsContext::create(GLFWwindow *windowHandler) {
        return make_unique<GraphicsContext>(windowHandler);
    }

    void GraphicsContext::init() {
        glfwMakeContextCurrent(m_windowHandler);
        if (!gladLoadGL()) {
            throw runtime_error("Failed to initialize GLAD");
        }
        cerr << "OpenGL " << glGetString(GL_VERSION) << endl;
    }

    void GraphicsContext::swapBuffers() {
        glfwSwapBuffers(m_windowHandler);
    }
}