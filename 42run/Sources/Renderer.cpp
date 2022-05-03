//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#include "Renderer.hpp"

namespace ft {
    void Renderer::draw(const std::shared_ptr<GameObject>& object, const std::shared_ptr<Camera>& camera) {
//        GLfloat *view = camera->transform()->inverseModel();
//        GLfloat *model = object->transform()->model();
//
//        object->meshRenderer()->drawMesh(view, model);
    }

    void Renderer::setClearColor(const glm::vec4& color) {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void Renderer::clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}
