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
        Model() : m_totalMeshes(0), m_min(glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX)), m_max(FLT_MIN, FLT_MIN, FLT_MIN)  {}
        explicit Model(const char *path) : Model() { loadModel(path); }

        void loadModel(const std::string& path);
        void loadBox(glm::vec3 center, float halfX, float halfY, float halfZ);

        std::vector<Mesh>::iterator begin() { return m_meshes.begin(); }
        std::vector<Mesh>::iterator end() { return m_meshes.end(); }
        glm::vec3 getMin() const { return m_min; }
        glm::vec3 getMax() const { return m_max; }

        void bindMesh(int i);

        int meshCounter() const { return m_totalMeshes; }
        std::shared_ptr<VertexBuffer> getVBO(int i);
        std::shared_ptr<ElementBuffer> getEBO(int i);
        std::shared_ptr<VertexArray> getVAO(int i);

    private:
        void loadInGPU();
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        // model data
        std::vector<Mesh> m_meshes;
        std::string m_directory;

        int m_totalMeshes;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::vector<std::shared_ptr<ElementBuffer>> m_indexBuffers;
        std::vector<std::shared_ptr<VertexArray>> m_vertexArrays;

        glm::vec3 m_min{};
        glm::vec3 m_max{};
    };
}

#endif //MODEL_HPP
