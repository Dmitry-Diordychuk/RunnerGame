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
        int i = 0;
        unsigned int offset = 0;
        std::for_each(elements.begin(), elements.end(),
        [stride, &i, &offset] (const VertexBufferElement& element){
            GLCall(glEnableVertexAttribArray(i));
            GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, stride, (void*)offset));
            offset += element.getSizeOfType() * element.count;
            i++;
        });
    }

    void VertexArray::bind() const {
        GLCall(glBindVertexArray(m_VAO));
    }

    void VertexArray::unbind() const {
        GLCall(glBindVertexArray(0));
    }
}