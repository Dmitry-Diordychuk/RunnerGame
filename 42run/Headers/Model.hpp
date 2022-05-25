//
// Created by ebona on 06.05.2022.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Pointer.hpp"

#include "Mesh.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"


namespace ft {
    using namespace std;

    class Model
    {
    public:
        Model() : m_totalMeshes(0), m_min(glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX)), m_max(FLT_MIN, FLT_MIN, FLT_MIN)  {}
        explicit Model(const char *path) : Model() { loadModel(path); }

        void loadModel(const string& path);
        void loadBox(glm::vec3 center, float halfX, float halfY, float halfZ);

        vector<Mesh>::iterator begin() { return m_meshes.begin(); }
        vector<Mesh>::iterator end() { return m_meshes.end(); }
        glm::vec3 getMin() const { return m_min; }
        glm::vec3 getMax() const { return m_max; }

        void bindMesh(int i);

        int meshCounter() const { return m_totalMeshes; }
        Ref<VertexBuffer> getVBO(int i);
        Ref<ElementBuffer> getEBO(int i);
        Ref<VertexArray> getVAO(int i);

    private:
        void loadInGPU();
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        // model data
        vector<Mesh> m_meshes;
        string m_directory;

        int m_totalMeshes;
        vector<Ref<VertexBuffer>> m_vertexBuffers;
        vector<Ref<ElementBuffer>> m_indexBuffers;
        vector<Ref<VertexArray>> m_vertexArrays;

        glm::vec3 m_min{};
        glm::vec3 m_max{};
    };
}

#endif //MODEL_HPP
