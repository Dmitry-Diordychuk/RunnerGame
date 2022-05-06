//
// Created by ebona on 06.05.2022.
//

#ifndef MODEL_HPP
#define MODEL_HPP

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Mesh.hpp"


namespace ft {
    class Model
    {
    private:
        // model data
        std::vector<Mesh> m_meshes;
        std::string m_directory;

    public:
        explicit Model(const char *path)
        {
            loadModel(path);
        }
        std::vector<Mesh>::iterator begin() { return m_meshes.begin(); }
        std::vector<Mesh>::iterator end() { return m_meshes.end(); }

    private:
        void loadModel(const std::string& path);
        void processNode(aiNode *node, const aiScene *scene);
        static Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        //static std::vector<ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    };
}

#endif //MODEL_HPP
