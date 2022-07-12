//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Renderer.hpp"

namespace ft {
    int Renderer::m_width;
    int Renderer::m_height;
    glm::vec4 Renderer::m_backgroundColor;
    Shader* Renderer::m_shader; // TODO: Указатель удаляется?
    Shader* Renderer::m_gizmoShader;
    Shader* Renderer::m_guiShader;

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

        m_gizmoShader = new Shader();
        m_gizmoShader->attach("/42run/Shaders/camera.vert");
        m_gizmoShader->attach("/42run/Shaders/basic.frag");
        m_gizmoShader->link();

        m_guiShader = new Shader();
        m_guiShader->attach("/42run/Shaders/gui.vert");
        m_guiShader->attach("/42run/Shaders/gui.frag");
        m_guiShader->link();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        if (gameObject.texture()) {
            gameObject.texture()->bind(0);
        }
        shader.activate();

        shader.bind("projection", camera.projectionMatrix());
        shader.bind("view", camera.transform()->inverseModel());
        shader.bind("model", gameObject.transform()->model());
        shader.bind("ambientLightingColor", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.bind("diffuseLightingColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.bind("lightPos", camera.transform()->position());

        if (gameObject.model()) {
            for (int i = 0; i < gameObject.model()->meshCounter(); i++) {
                gameObject.model()->bindMesh(i);
                GLCall(glDrawElements(
                        GL_TRIANGLES,
                        gameObject.model()->getEBO(i)->getCount(),
                        GL_UNSIGNED_INT,
                        nullptr));
            }
        }
    }

    void Renderer::draw(const GameObject& gameObject, const Camera& camera) {
        draw(*m_shader, gameObject, camera);
    }

    void Renderer::drawCollider(const GameObject &gameObject, const Camera &camera) {
        if (gameObject.colliders().size() > 0)
        {
            m_gizmoShader->activate();

            m_gizmoShader->bind("projection", camera.projectionMatrix());
            m_gizmoShader->bind("view", camera.transform()->inverseModel());
            m_gizmoShader->bind("model", gameObject.transform()->modelWithoutRotation());

            for (auto &collider : gameObject.colliders()) {
                collider->model()->bindMesh(0);
                GLCall(glDrawElements(
                        GL_LINE_LOOP,
                        collider->model()->getEBO(0)->getCount(),
                        GL_UNSIGNED_INT,
                        nullptr));
            }
        }
    }

    void Renderer::drawText(const GameObject &gameObject, int screenWidth, int screenHeight) {
        if (!gameObject.text()) {
            return;
        }

        gameObject.text()->font()->texture()->bind(0);

        m_guiShader->activate();

        m_guiShader->bind("screen", glm::vec3(screenWidth, screenHeight, 0.0f));

        for (auto &glyph : *gameObject.text())
        {
            glyph->bindMesh(0);
            GLCall(glDrawElements(
                    GL_TRIANGLES,
                    glyph->getEBO(0)->getCount(),
                    GL_UNSIGNED_INT,
                    nullptr));
        }
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
