//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Screen.hpp"

void ft::Screen::open(int screenWidth, int screenHeight, const std::string &title, bool isFullScreen) {
    _title = title;

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWmonitor *primary = nullptr;
    if (isFullScreen) {
        primary = glfwGetPrimaryMonitor();
    }

    _window = glfwCreateWindow(
            screenWidth,
            screenHeight,
            _title.c_str(),
            primary,
            nullptr
    );

    // Check for Valid Context
    if (_window == nullptr) {
        throw std::runtime_error("Failed to Create OpenGL Context");
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(_window);
    if (!gladLoadGL())
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cerr << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    // Как отобразить нормализованные координаты (в диапозоне от -1 до 1) на кординаты окна
    glViewport(0, 0, screenWidth, screenHeight);

    glfwSetFramebufferSizeCallback(_window, windowResizeCallback);
}

void ft::Screen::display() {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(_window, true);
    }

    // Flip Buffers and Draw
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void ft::Screen::close() {
    glfwTerminate();
}

void ft::Screen::clear() {
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f); // TODO: background color, color class
    glClear(GL_COLOR_BUFFER_BIT);
}

bool ft::Screen::isOpen() {
    return glfwWindowShouldClose(_window) == false;
}


// Private methods

void ft::Screen::windowResizeCallback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}


