//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Renderer.hpp"
#include "Camera.hpp"

namespace ft {
    int Renderer::m_width;
    int Renderer::m_height;
    glm::vec4 Renderer::m_backgroundColor;
    Shader* Renderer::m_shader;

    void Renderer::init(int width, int height, const glm::vec4& backgroundColor) {
        ASSERT(width > 0)
        ASSERT(height > 0)
        ASSERT(backgroundColor.r >= 0.0f)
        ASSERT(backgroundColor.g >= 0.0f)
        ASSERT(backgroundColor.b >= 0.0f)
        ASSERT(backgroundColor.a >= 0.0f)

        m_width = width;
        m_height = height;
        m_backgroundColor = backgroundColor;

        m_shader = new Shader();
        m_shader->attach("/42run/Shaders/camera.vert"); // TODO: прокинуть другие шейдеры
        m_shader->attach("/42run/Shaders/illumination.frag");
        m_shader->link();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    }

    void Renderer::draw(Shader& shader, const VertexArray& vertexArray, const ElementBuffer& indexBuffer) {
        shader.activate();
        vertexArray.bind();
        indexBuffer.bind();

        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
    }

    void Renderer::draw(Shader &shader, const GameObject& gameObject, const Camera& camera) {
        gameObject.texture()->bind(0);
        shader.activate();

        shader.bind("projection", camera.projectionMatrix());
        shader.bind("view", camera.transform()->inverseModel());
        shader.bind("model", gameObject.transform()->model());
        shader.bind("ambientLightingColor", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.bind("diffuseLightingColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.bind("lightPos", glm::vec3(3.0f, 2.0f, 0.0f));

        for (int i = 0; i < gameObject.model()->meshCounter(); i++)
        {
            gameObject.model()->bindMesh(i);
            GLCall(glDrawElements(GL_TRIANGLES, gameObject.model()->getEBO(i)->getCount(), GL_UNSIGNED_INT, nullptr));
        }
    }

    void Renderer::draw(const GameObject& gameObject, const Camera& camera) {
        draw(*m_shader, gameObject, camera);
    }


    void Renderer::setClearColor(const glm::vec4& color) {
        ASSERT(color.r >= 0.0f)
        ASSERT(color.g >= 0.0f)
        ASSERT(color.b >= 0.0f)
        ASSERT(color.a >= 0.0f)

        m_backgroundColor = color;
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
