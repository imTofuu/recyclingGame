#include "AssetFetcher.h"

#include <cstdio>
#include <cstring>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Logger.h"
#include "Graphics/Vector.h"

namespace RecyclingGame {

    Model* AssetFetcher::m_lightModel = nullptr;

    Model AssetFetcher::modelFromPath(const char* path) {

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenNormals);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            Logger::error("Failed to load model from file " + std::string(path) + ": " + importer.GetErrorString());
            return {};
        }

        Model model;

        processModelNode(model, scene->mRootNode, scene);

        return model;
    }

    void AssetFetcher::processModelNode(Model& model, aiNode* node, const aiScene* scene) {
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model.addMesh(processMesh(mesh, scene));
        }

        for (int i = 0; i < node->mNumChildren; i++) {
            processModelNode(model, node->mChildren[i], scene);
        }
    }

    Mesh AssetFetcher::processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vector3> vertices, normals;
        std::vector<Vector2> uvs;
        std::vector<unsigned int> indices;

        for (int i = 0; i < mesh->mNumVertices; i++) {
            Vector3 vertexPosition;
            vertexPosition.x = mesh->mVertices[i].x;
            vertexPosition.y = mesh->mVertices[i].y;
            vertexPosition.z = mesh->mVertices[i].z;

            vertices.push_back(vertexPosition);

            Vector3 normal;
            if (mesh->HasNormals()) {
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;
            }

            normals.push_back(normal);

            Vector2 uv;
            if (mesh->HasTextureCoords(0)) {
                uv.x = mesh->mTextureCoords[0][i].x;
                uv.y = mesh->mTextureCoords[0][i].y;
            } else {
                uv = { 0.0f, 0.0f };
            }

            uvs.push_back(uv);
        }

        for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        Mesh result;

        VertexBuffer normalBuffer;
        normalBuffer.setData(normals.data(), vertices.size() * sizeof(Vector3));

        VertexBuffer uvBuffer;
        uvBuffer.setData(uvs.data(), vertices.size() * sizeof(Vector2));

        result.setVertices(reinterpret_cast<float*>(vertices.data()), static_cast<unsigned int>(vertices.size()));
        result.setIndices(indices.data(), indices.size());

        result.setBuffer(1, normalBuffer, BufferLayout::ElementType::FLOAT3);
        result.setBuffer(2, uvBuffer, BufferLayout::ElementType::FLOAT2);

        return result;
    }


    Texture AssetFetcher::textureFromFile(const char* path) {
        int width, height;
        unsigned char* data = stbi_load(path, &width, &height, nullptr, 4);

        if (!data) {
            Logger::error("Failed to load texture from file: " + std::string(path));
            Logger::error(stbi_failure_reason());
            return {};
        }
        
        Texture texture(reinterpret_cast<char*>(data), static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        stbi_image_free(data);
        return texture;
    }
    
}
