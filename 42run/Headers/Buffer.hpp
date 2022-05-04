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
        unsigned int m_count;

    public:
        VertexBuffer();
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void load(const GLfloat *vertices, size_t count);

        unsigned int getCount() const { return m_count; }
    };

    class ElementBuffer {
    private:
        GLuint m_EBO{};
        unsigned int m_count;

    public:
        ElementBuffer();
        ~ElementBuffer();

        void bind() const;
        void unbind() const;

        void load(const GLuint *indices, size_t count);

        unsigned int getCount() const { return m_count; }
    };
}

#endif //BUFFER_HPP
