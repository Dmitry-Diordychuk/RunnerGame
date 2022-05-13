//
// Created by ebona on 06.05.2022.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"


namespace ft {
    class Model
    {
    public:
        Model() = default;
        explicit Model(const char *path) { loadModel(path); }
        void loadModel(const std::string& path);
        std::vector<Mesh>::iterator begin() { return m_meshes.begin(); }
        std::vector<Mesh>::iterator end() { return m_meshes.end(); }

        void bindMesh(int i);

        int meshCounter() const { return m_totalMeshes; }
        std::shared_ptr<VertexBuffer> getVBO(int i);
        std::shared_ptr<ElementBuffer> getEBO(int i);
        std::shared_ptr<VertexArray> getVAO(int i);

    private:
        void loadInGPU();
        void processNode(aiNode *node, const aiScene *scene);
        static Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        // model data
        std::vector<Mesh> m_meshes;
        std::string m_directory;

        int m_totalMeshes = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::vector<std::shared_ptr<ElementBuffer>> m_indexBuffers;
        std::vector<std::shared_ptr<VertexArray>> m_vertexArrays;

    };
}

#endif //MODEL_HPP
