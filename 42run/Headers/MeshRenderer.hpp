//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_MESHRENDERER_HPP
#define GLITTER_MESHRENDERER_HPP

#include <iostream>
#include <utility>

#include "Mesh.hpp"

namespace ft {
    class MeshRenderer {
    private:
        ft::Mesh _mesh;

        // Private Member Variables
        GLuint _vertexArray;
        //GLuint mVertexBuffer{};
        //GLuint mElementBuffer{};


    public:
        // Implement Default Constructor and Destructor
        MeshRenderer() { std::cout << "VAO" << std::endl; glGenVertexArrays(1, & _vertexArray); }
        ~MeshRenderer() { glDeleteVertexArrays(1, & _vertexArray); }

        // Implement Custom Constructors
        // explicit MeshRenderer(const ft::Mesh &mesh);

        // Public Member Functions
        void drawMesh(GLuint);

        void setMesh(Mesh mesh) { _mesh = std::move(mesh); }

        // Disable Copying and Assignment
        MeshRenderer(MeshRenderer const &) = delete;
        MeshRenderer & operator=(MeshRenderer const &) = delete;


    private:

    };

}

#endif //GLITTER_MESHRENDERER_HPP
