#pragma once

#include "Texture.hpp"
#include "Vertex.hpp"

#include <utility>
#include <vector>



namespace ft {
    using namespace std;

    class Mesh {
    private:
        vector<Vertex> m_vertices;
        vector<GLuint> m_indices;
        vector<ModelTexture> m_texture;

    public:
        Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<ModelTexture> texture)
            : m_vertices(move(vertices)), m_indices(move(indices)), m_texture(move(texture))
        {}

        vector<Vertex> vertices() { return m_vertices; }
        vector<GLuint> indices() { return m_indices; }
        vector<ModelTexture> texture() { return m_texture; }
    };
};
