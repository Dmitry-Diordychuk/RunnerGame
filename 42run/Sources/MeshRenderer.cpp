//
// Created by Diordychuk Dmitry on 27.04.2022.
//

#include "MeshRenderer.hpp"

namespace ft {
//    ft::MeshRenderer::MeshRenderer(const ft::Mesh &mesh) : _mesh(mesh) {
//        // Bind a Vertex Array Object
//        glGenVertexArrays(1, & mVertexArray);
//        glBindVertexArray(mVertexArray);
//
//        // Copy Vertex Buffer Data
//        glGenBuffers(1, & mVertexBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
//        glBufferData(GL_ARRAY_BUFFER,
//                     _mesh.vertices.size() * sizeof(Vertex),
//                     & _mesh.vertices.front(), GL_STATIC_DRAW);
//
//        // Copy Index Buffer Data
//        glGenBuffers(1, & mElementBuffer);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementBuffer);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                     _mesh.indices.size() * sizeof(GLuint),
//                     & _mesh.indices.front(), GL_STATIC_DRAW);
//
//        // Set Shader Attributes
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position));
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, normal));
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, uv));
//        glEnableVertexAttribArray(0); // Vertex Positions
//        glEnableVertexAttribArray(1); // Vertex Normals
//        glEnableVertexAttribArray(2); // Vertex UVs
//
//        // Cleanup Buffers
//        glBindVertexArray(0);
//        glDeleteBuffers(1, & mVertexBuffer);
//        glDeleteBuffers(1, & mElementBuffer);
//    }

    void MeshRenderer::draw(GLuint)
    {
        //unsigned int unit = 0, diffuse = 0, specular = 0;
//        for (auto &i : _mesh.texture)
//        {   // Set Correct Uniform Names Using Texture Type (Omit ID for 0th Texture)
//            std::string uniform = i.second;
//            if (i.second == "diffuse")  uniform += (diffuse++  > 0) ? std::to_string(diffuse)  : "";
//            else if (i.second == "specular") uniform += (specular++ > 0) ? std::to_string(specular) : "";
//
//            // Bind Correct Textures and Vertex Array Before Drawing
//            glActiveTexture(GL_TEXTURE0 + unit);
//            glBindTexture(GL_TEXTURE_2D, i.first);
//            glUniform1f(glGetUniformLocation(shader, uniform.c_str()), ++unit);
//        }
        //glBindVertexArray(mVertexArray);
        //glDrawElements(GL_TRIANGLES, _mesh.indices.size(), GL_UNSIGNED_INT, 0);
    }

}