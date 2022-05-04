//
// Created by ebona on 02.05.2022.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <utility>

#include "Consts.hpp"
#include "GraphicsContext.hpp"
#include "GlError.hpp"


namespace ft{
    struct WindowProps
    {
        std::string title;
        int width, height;

        explicit WindowProps(
            std::string  title = Consts::DEFAULT_WINDOW_TITLE,
            int width = Consts::DEFAULT_WINDOW_WIDTH,
            int height = Consts::DEFAULT_WINDOW_HEIGHT)
        : title(title), width(width), height(height)
        {

        }
    };

    class Window {
    private:
        GLFWwindow *m_window{};
        std::unique_ptr<GraphicsContext> m_context;
        WindowProps m_windowProps;

    public:
        Window() = default;
        ~Window() = default;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        void open(const WindowProps& props);
        static void close();

        void update();

        bool isOpen();

        WindowProps getProps() const { return m_windowProps; }
    };
}

#endif //WINDOW_HPP
