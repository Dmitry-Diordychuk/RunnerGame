#pragma once

#include "glad/glad.h"

#include <vector>

#include "Vertex.hpp"
#include "Texture.hpp"

// Define Namespace
namespace ft {
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> texture;
    };
};
