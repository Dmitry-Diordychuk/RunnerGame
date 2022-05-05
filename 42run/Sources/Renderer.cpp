//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Renderer.hpp"

namespace ft {
    void Renderer::init(int width, int height) {
        ASSERT(width > 0)
        ASSERT(height > 0)

        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::draw(const Shader& shader, const VertexArray& vertexArray, const ElementBuffer& indexBuffer) {
        shader.activate();
        vertexArray.bind();
        indexBuffer.bind();

        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::setClearColor(const glm::vec4& color) {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
