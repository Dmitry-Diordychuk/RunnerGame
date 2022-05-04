//
// Created by ebona on 03.05.2022.
//

#include "VertexArray.hpp"

namespace ft{
    VertexArray::VertexArray() { GLCall(glGenVertexArrays(1, (GLuint*)&m_VAO)); }
    VertexArray::~VertexArray() { GLCall(glDeleteVertexArrays(1, &m_VAO)); }

    void VertexArray::addBuffer(const VertexBuffer &VBO, const VertexBufferLayout &layout) {
        bind();

        VBO.bind();

        const std::vector<VertexBufferElement>& elements = layout.getElements();
        const unsigned int stride = layout.getStride();

        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const VertexBufferElement& element = elements[i];
            GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, stride, (void*)offset));
            GLCall(glEnableVertexAttribArray(i));
            offset += element.getSizeOfType() * element.count;
        }
    }

    void VertexArray::bind() const {
        GLCall(glBindVertexArray(m_VAO));
    }

    void VertexArray::unbind() const {
        GLCall(glBindVertexArray(0));
    }
}