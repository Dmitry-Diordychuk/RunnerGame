//
// Created by ebona on 03.05.2022.
//

#include "Buffer.hpp"

namespace ft{
    VertexBuffer::VertexBuffer() : m_count(0) {
        GLCall(glGenBuffers(1, (GLuint *)(&m_VBO)));
    }

    VertexBuffer::~VertexBuffer() {
        GLCall(glDeleteBuffers(1, &m_VBO));
    }

    void VertexBuffer::bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBO));
    }

    void VertexBuffer::unbind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    void VertexBuffer::load(const GLfloat *vertices, size_t count) {
        GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), vertices, GL_STATIC_DRAW));
        m_count = count;
    }

    ElementBuffer::ElementBuffer() : m_count(0) {
        GLCall(glGenBuffers(1, (GLuint*)&m_EBO));
    }

    ElementBuffer::~ElementBuffer() {
        GLCall(glDeleteBuffers(1, &m_EBO));
    }

    void ElementBuffer::bind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO));
    }

    void ElementBuffer::unbind() const {
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    void ElementBuffer::load(const GLuint *indices, size_t count) {
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), indices, GL_STATIC_DRAW));
        m_count = count;
    }
}