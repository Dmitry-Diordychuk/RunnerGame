//
// Created by Diordychuk Dmitry on 26.04.2022.
//

#ifndef RENDERER_HPP
#define RENDERER_HPP

// Local Headers
#include "glitter.hpp"

// System Headers
#include <iostream>

#include <memory>

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Buffer.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"


namespace ft {
    class Renderer {
    public:
        static void init(int width, int height, const glm::vec4& backgroundColor);

        static void draw(Shader& shader, const VertexArray& vertexArray, const ElementBuffer& indexBuffer);
        static void draw(Shader& shader, const GameObject& gameObject, const Camera& camera);
        static void draw(const GameObject& gameObject, const Camera& camera);


        static void setClearColor(const glm::vec4& color);
        static void clear();

    private:
        static int m_width, m_height;
        static glm::vec4 m_backgroundColor;
        static Shader* m_shader;

    };
}

#endif //RENDERER_HPP
