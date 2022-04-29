//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef GLITTER_SCREEN_HPP
#define GLITTER_SCREEN_HPP

// Local Headers
#include "glitter.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <exception>
#include <iostream>

#include "Consts.hpp"

namespace ft {
    class Screen {
    private:
        std::string _title = "";

        GLFWwindow* _window = nullptr;

    public:
        void open(
                int screenWidth = Consts::DEFAULT_SCREEN_WIDTH,
                int screenHeight = Consts::DEFAULT_SCREEN_HEIGHT,
                const std::string &title = Consts::DEFAULT_PROJECT_NAME,
                bool isFullScreen = false
        );

        void display();

        void close();

        void clear();

        bool isOpen();

    private:
        static void windowResizeCallback(GLFWwindow* window, int width, int height);
    };
}

#endif //GLITTER_SCREEN_HPP
