#pragma once

#include "glad/glad.h"

#include <utility>
#include <vector>

#include "Vertex.hpp"
#include "Texture.hpp"


namespace ft {
    class Mesh {
    private:
        std::vector<Vertex> m_vertices;
        std::vector<GLuint> m_indices;
        std::vector<ModelTexture> m_texture;

    public:
        Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<ModelTexture> texture)
            : m_vertices(std::move(vertices)), m_indices(std::move(indices)), m_texture(std::move(texture))
        {}

        std::vector<Vertex> vertices() { return m_vertices; }
        std::vector<GLuint> indices() { return m_indices; }
        std::vector<ModelTexture> texture() { return m_texture; }
    };
};
