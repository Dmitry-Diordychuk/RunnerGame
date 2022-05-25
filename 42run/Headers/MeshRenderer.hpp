//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#ifndef GLITTER_MESHRENDERER_HPP
#define GLITTER_MESHRENDERER_HPP

#include <iostream>
#include <utility>

#include "Mesh.hpp"
#include "Shader.hpp"

#include "Pointer.hpp"

namespace ft {
    class MeshRenderer {
    private:
        Ref<Mesh> _mesh;
        Ref<Shader> _shader;

        // Private Member Variables
        GLuint _VAO;
        GLuint _VBO;
        GLuint _EBO;

        bool _isInit = false;

    public:
        // Implement Default Constructor and Destructor
        MeshRenderer() = default;
        ~MeshRenderer() { if (_isInit) glDeleteVertexArrays(1, & _VAO); }

        // Implement Custom Constructors
        // explicit MeshRenderer(const ft::Mesh &mesh);

        // Public Member Functions
        void init();

        void setMesh(const Ref<Mesh>& mesh) { _mesh = mesh; }
        void setShader(const Ref<Shader>& shader) { _shader = shader; }

        //void loadShaders(const std::string& shaderVert, const std::string& shaderFrag, const std::string& shaderGeom);

        void drawMesh(GLfloat *view, GLfloat *model);

        // Disable Copying and Assignment
        MeshRenderer(MeshRenderer const &) = delete;
        MeshRenderer & operator=(MeshRenderer const &) = delete;


    private:

    };

}

#endif //GLITTER_MESHRENDERER_HPP
