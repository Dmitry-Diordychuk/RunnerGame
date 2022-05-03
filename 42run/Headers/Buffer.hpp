//
// Created by ebona on 02.05.2022.
//

#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "glad/glad.h"

#include "GlError.hpp"

namespace ft {
    class VertexBuffer {
    private:
        GLuint m_VBO{};

    public:
        VertexBuffer();
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void load(const GLfloat *vertices, size_t count);
    };

    class ElementBuffer {
    private:
        GLuint m_EBO{};

    public:
        ElementBuffer();
        ~ElementBuffer();

        void bind() const;
        void unbind() const;

        void load(const GLuint *indices, size_t count);

    };
}

#endif //BUFFER_HPP
