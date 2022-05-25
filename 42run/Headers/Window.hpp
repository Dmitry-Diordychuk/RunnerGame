//
// Created by ebona on 02.05.2022.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
//#include <glad/glad.h>

#include <string>
#include <utility>

#include "Pointer.hpp"

#include "Consts.hpp"
#include "GraphicsContext.hpp"
#include "GlError.hpp"
#include "Event.hpp"


namespace ft{
    using namespace std;

    struct WindowProps
    {
        string title;
        int width, height;
        Ref<Event> event;

        explicit WindowProps(
            string title = Consts::DEFAULT_WINDOW_TITLE,
            int width = Consts::DEFAULT_WINDOW_WIDTH,
            int height = Consts::DEFAULT_WINDOW_HEIGHT)
        : title(move(title)), width(width), height(height), event(nullptr)
        {

        }
    };

    class Window {
    private:
        GLFWwindow *m_window{};
        Scope<GraphicsContext> m_context;
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
