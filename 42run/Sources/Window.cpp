//
// Created by ebona on 02.05.2022.
//

#include "Window.hpp"


namespace ft {
    void Window::open(const WindowProps &props) {
        ASSERT(props.width > 0);
        ASSERT(props.height > 0);
        m_windowProps.title = props.title;
        m_windowProps.width = props.width;
        m_windowProps.height = props.height;

        // Load GLFW and create a Window
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        m_window = glfwCreateWindow(
                props.width,
                props.height,
                props.title.c_str(),
                nullptr,
                nullptr
        );

        // Check for Valid Context
        if (m_window == nullptr) {
            throw std::runtime_error("Failed to create OpenGL Context");
        }

        m_context = GraphicsContext::create(m_window);
        m_context->init();
    }

    void Window::close() {
        glfwTerminate();
    }

    void Window::update() {
        m_context->swapBuffers();
        glfwPollEvents();
    }

    bool Window::isOpen() {
        return glfwWindowShouldClose(m_window) == false;
    }
}
