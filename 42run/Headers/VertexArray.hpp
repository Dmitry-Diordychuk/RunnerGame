//
// Created by ebona on 02.05.2022.
//

#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glad/glad.h"

#include "Buffer.hpp"

#include <vector>
#include <algorithm>

namespace ft {
    using namespace std;

    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        bool normalized;

        unsigned int getSizeOfType() const
        {
            switch (this->type) {
                case GL_FLOAT: return sizeof(GLfloat);
                case GL_UNSIGNED_INT: return sizeof(GLuint);
            }
            ASSERT(false);
            return 0;
        }
    };

    class VertexBufferLayout
    {
    private:
        vector<VertexBufferElement> m_elements;
        unsigned int m_stride;

    public:
        VertexBufferLayout() : m_stride(0) {}

        template<typename T>
        void push(unsigned int count)
        {
            ASSERT(false)
        }

        template<>
        void push<GLfloat>(unsigned int count)
        {
            m_elements.push_back(VertexBufferElement { GL_FLOAT, count, false });
            m_stride += sizeof(GLfloat) * count;
        }

        template<>
        void push<GLuint>(unsigned int count)
        {
            m_elements.push_back(VertexBufferElement { GL_UNSIGNED_INT, count, false });
            m_stride += sizeof(GLuint) * count;
        }

        inline const vector<VertexBufferElement>& getElements() const { return m_elements; }
        inline unsigned int getStride() const { return m_stride; }
    };

    class VertexArray {
    private:
        GLuint m_VAO{};

    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

        void addBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout);
    };
}


#endif //VERTEXARRAY_HPP
