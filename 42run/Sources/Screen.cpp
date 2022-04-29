//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Screen.hpp"

namespace ft {

    void Screen::open(int screenWidth, int screenHeight, const std::string &title, bool isFullScreen) {
        _title = title;

        // Load GLFW and Create a Window
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef  __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

        if (!gladLoadGL()) {
            throw std::runtime_error("Failed to initialize GLAD");
        }
        std::cerr << "OpenGL " << glGetString(GL_VERSION) << std::endl;

        // Как отобразить нормализованные координаты (в диапозоне от -1 до 1) на кординаты окна
        glViewport(0, 0, screenWidth, screenHeight);

        glfwSetFramebufferSizeCallback(_window, windowResizeCallback);
    }

    void Screen::prepareGLToDraw() {

    }

    void Screen::display() {
        if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(_window, true);
        }

        // Flip Buffers and Draw
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }

    void Screen::drawMesh(Mesh mesh) {
        GLuint VAO; // Bind a Vertex Array Object
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        float vertices[] = {
                0.5f, 0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };
        unsigned int indices[] = {
                0,1,3,
                1,2,3
        };

        GLuint VBO; // Copy vertices array in vertex buffer for OpenGL to use
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferData(GL_ARRAY_BUFFER,
//                     sizeof(Vertex) * mesh.vertices.size(),
//                     &mesh.vertices.front(),
//                     GL_STATIC_DRAW);
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLuint EBO; // Copy index array in a element buffer for OpenGL to use
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                     sizeof(GLuint) * mesh.indices.size(),
//                     &mesh.indices.front(),
//                     GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(indices),
                     indices,
                     GL_STATIC_DRAW);

        // Set vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, position));
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, uv));
        glEnableVertexAttribArray(0);
        //glEnableVertexAttribArray(1);
        //glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Cleanup Buffers
        //glBindVertexArray(0);
        //glDeleteBuffers(1, &VBO);
        //glDeleteBuffers(1, &EBO);

        glUseProgram(0);
        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, counter);
    }


    void Screen::close() {
        glfwTerminate();
    }

    void Screen::clear() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // TODO: background color, color class
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool Screen::isOpen() {
        return glfwWindowShouldClose(_window) == false;
    }


// Private methods

    void Screen::windowResizeCallback(GLFWwindow *, int width, int height) {
        glViewport(0, 0, width, height);
    }
}
