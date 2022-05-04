//
// Created by Diordychuk Dmitry on 28.04.2022.
//

//#include "AssetProcessor.hpp"

//namespace ft {
//
//    void AssetProcessor::processAsset(const std::string &filename) {
//        const aiScene *scene = loadAsset(filename);
//        parseAsset(scene, scene->mRootNode);
//    }
//
//    const aiScene *AssetProcessor::loadAsset(const std::string &filename) {
//        // Load a Model from File
//        Assimp::Importer loader;
//        aiScene const *scene = loader.ReadFile(
//                PROJECT_SOURCE_DIR "/Mirage/Models/" + filename,
//                aiProcessPreset_TargetRealtime_MaxQuality |
//                aiProcess_OptimizeGraph |
//                aiProcess_FlipUVs);
//
//        if (!scene) {
//            throw std::runtime_error(std::string("Assimp lib error::") + std::string(loader.GetErrorString()));
//        }
//
//        return (scene);
//    }
//
//    std::vector<ft::Mesh> AssetProcessor::parseAsset(const aiScene *scene, const aiNode *node) {
//        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
//            .push_back(parseAsset(scene, scene->mMeshes[node->mMeshes[i]]));
//        }
//        for (unsigned int i = 0; i < node->mNumChildren; i++) {
//            parseAsset(scene, node->mChildren[i]);
//        }
//
//        return std::vector<ft::Mesh>();
//    }
//
//    void AssetProcessor::parseAsset(const aiScene *scene, aiMesh const *mesh) {
//        std::vector<Vertex> vertices;
//        std::vector<GLuint> indices;
//        std::vector<Texture> textures;
//
//        // create Vertex Data from Mesh Node
//        Vertex vertex;
//        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
//            if (mesh->mTextureCoords[0])
//                vertex.uv = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
//            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//            vertices.push_back(vertex);
//        }
//
//        // create Mesh Indices for Indexed Drawing
//        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//            for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
//                indices.push_back(mesh->mFaces[i].mIndices[j]);
//
//        //return Mesh::Mesh()
//    }
//}
