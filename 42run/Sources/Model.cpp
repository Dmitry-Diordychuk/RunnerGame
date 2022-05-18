//
// Created by ebona on 06.05.2022.
//

#include "Model.hpp"

namespace ft
{
    void ft::Model::loadModel(const std::string& path) {
        Assimp::Importer import;
        std::string projectDir = PROJECT_SOURCE_DIR;
        const aiScene *scene = import.ReadFile( projectDir + path, aiProcessPreset_TargetRealtime_Fast);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
            ASSERT(false)
        }
        m_directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);

        loadInGPU();
    }

    void Model::loadBox(glm::vec3 center, float halfX, float halfY, float halfZ) {
        std::vector<Vertex> vertices = {
            Vertex{glm::vec3(center.x - halfX, center.y - halfY, center.z - halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x - halfX, center.y + halfY, center.z - halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x + halfX, center.y - halfY, center.z - halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x + halfX, center.y + halfY, center.z - halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},

            Vertex{glm::vec3(center.x - halfX, center.y - halfY, center.z + halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x - halfX, center.y + halfY, center.z + halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x + halfX, center.y - halfY, center.z + halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
            Vertex{glm::vec3(center.x + halfX, center.y + halfY, center.z + halfZ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        };

        std::vector<GLuint> indices = {
            0, 1, 1, 3, 3, 2, 2, 0,
            0, 4, 4, 5, 5, 1, 1, 4,
            4, 6, 6, 7, 7, 5, 5, 6,
            6, 2, 2, 3, 3, 7, 7, 2,
            2, 4, 5, 3
        };

        std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>();
        vertexBuffer->bind();
        vertexBuffer->load((GLfloat*)&vertices[0], vertices.size() * (3 + 3 + 2));

        VertexBufferLayout layout;
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(3);
        layout.push<GLfloat>(2);

        std::unique_ptr<VertexArray> vertexArray = std::make_unique<VertexArray>();
        vertexArray->addBuffer(*vertexBuffer, layout);


        std::unique_ptr<ElementBuffer> indexBuffer = std::make_unique<ElementBuffer>();
        indexBuffer->bind();
        indexBuffer->load(&indices[0], indices.size());

        m_vertexBuffers.push_back(std::move(vertexBuffer));
        m_vertexArrays.push_back(std::move(vertexArray));
        m_indexBuffers.push_back(std::move(indexBuffer));
        m_totalMeshes++;
    }

    void Model::loadInGPU() {
        for (auto& it: m_meshes)
        {
            std::vector<Vertex> vertices = it.vertices();
            std::vector<GLuint> indices = it.indices();

            std::unique_ptr<VertexBuffer> vertexBuffer = std::make_unique<VertexBuffer>();
            vertexBuffer->bind();
            vertexBuffer->load((GLfloat*)&vertices[0], vertices.size() * (3 + 3 + 2));

            VertexBufferLayout layout;
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(3);
            layout.push<GLfloat>(2);

            std::unique_ptr<VertexArray> vertexArray = std::make_unique<VertexArray>();
            vertexArray->addBuffer(*vertexBuffer, layout);


            std::unique_ptr<ElementBuffer> indexBuffer = std::make_unique<ElementBuffer>();
            indexBuffer->bind();
            indexBuffer->load(&indices[0], indices.size());

            m_vertexBuffers.push_back(std::move(vertexBuffer));
            m_vertexArrays.push_back(std::move(vertexArray));
            m_indexBuffers.push_back(std::move(indexBuffer));
            m_totalMeshes++;
        }
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; // contains index to a mesh in Scene.mMeshes[]
            m_meshes.push_back(processMesh(mesh, scene));
        }
        // then do the same for each of its children
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *) {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<ModelTexture> textures;

        // walk through each of the mesh's vertices
        for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            if (vector.x < m_min.x) {
                m_min = glm::vec3(vector.x, m_min.y, m_min.z);
            }
            if (vector.y < m_min.y) {
                m_min = glm::vec3(m_min.x, vector.y, m_min.z);
            }
            if (vector.z < m_min.z) {
                m_min = glm::vec3(m_min.x, m_min.y, vector.z);
            }

            if (vector.x > m_max.x) {
                m_max = glm::vec3(vector.x, m_max.y, m_max.z);
            }
            if (vector.y > m_max.y) {
                m_max = glm::vec3(m_max.x, vector.y, m_max.z);
            }
            if (vector.z > m_max.z) {
                m_max = glm::vec3(m_max.x, m_max.y, vector.z);
            }

            // normals
            if (mesh->HasNormals()) {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.uv = vec;
                // tangent
//                vector.x = mesh->mTangents[i].x;
//                vector.y = mesh->mTangents[i].y;
//                vector.z = mesh->mTangents[i].z;
                //vertex.Tangent = vector;
                // bitangent
//                vector.x = mesh->mBitangents[i].x;
//                vector.y = mesh->mBitangents[i].y;
//                vector.z = mesh->mBitangents[i].z;
                //vertex.Bitangent = vector;
            } else
                vertex.uv = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
//        // process materials
//        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
//        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
//        // Same applies to other texture as the following list summarizes:
//        // diffuse: texture_diffuseN
//        // specular: texture_specularN
//        // normal: texture_normalN
//
//        // 1. diffuse maps
//        std::vector<ModelTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//        // 2. specular maps
//        std::vector<ModelTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//        // 3. normal maps
//        std::vector<ModelTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//        // 4. height maps
//        std::vector<ModelTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
//
//        // return a mesh object created from the extracted mesh data
        return Mesh(vertices, indices, textures);
    }

    std::shared_ptr<VertexBuffer> Model::getVBO(int i) {
        return m_vertexBuffers[i];
    }

    std::shared_ptr<ElementBuffer> Model::getEBO(int i) {
        return m_indexBuffers[i];
    }

    std::shared_ptr<VertexArray> Model::getVAO(int i) {
        return m_vertexArrays[i];
    }

    void Model::bindMesh(int i) {
        m_vertexArrays[i]->bind();
        m_indexBuffers[i]->bind();
    }


//    std::vector<ModelTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName) {
//        string filename = string(path);
//        filename = directory + '/' + filename;
//
//        unsigned int textureID;
//        glGenTextures(1, &textureID);
//
//        int width, height, nrComponents;
//        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
//        if (data)
//        {
//            GLenum format;
//            if (nrComponents == 1)
//                format = GL_RED;
//            else if (nrComponents == 3)
//                format = GL_RGB;
//            else if (nrComponents == 4)
//                format = GL_RGBA;
//
//            glBindTexture(GL_TEXTURE_2D, textureID);
//            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//            glGenerateMipmap(GL_TEXTURE_2D);
//
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            stbi_image_free(data);
//        }
//        else
//        {
//            std::cout << "Texture failed to load at path: " << path << std::endl;
//            stbi_image_free(data);
//        }
//
//        return textureID;
//    }
}