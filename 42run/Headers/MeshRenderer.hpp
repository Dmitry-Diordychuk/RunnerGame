//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_MESHRENDERER_HPP
#define GLITTER_MESHRENDERER_HPP

#include <utility>

#include "Mesh.hpp"

namespace ft {
    class MeshRenderer {
    private:
        ft::Mesh _mesh;

        // Private Member Variables
        GLuint mVertexArray{};
        GLuint mVertexBuffer{};
        GLuint mElementBuffer{};


    public:
        // Implement Default Constructor and Destructor
        MeshRenderer() {}; //glGenVertexArrays(1, & mVertexArray); }
        ~MeshRenderer() {}; //glDeleteVertexArrays(1, & mVertexArray); }

        // Implement Custom Constructors
        // explicit MeshRenderer(const ft::Mesh &mesh);

        // Public Member Functions
        void draw(GLuint);

        void setMesh(Mesh mesh) { _mesh = std::move(mesh); }

        // Disable Copying and Assignment
        MeshRenderer(MeshRenderer const &) = delete;
        MeshRenderer & operator=(MeshRenderer const &) = delete;


    private:

    };

}

#endif //GLITTER_MESHRENDERER_HPP
