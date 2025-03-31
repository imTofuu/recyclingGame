#include "AssetFetcher.h"

#include <cstdio>
#include <stb_image.h>

#include "Logger.h"
#include "Graphics/Vector.h"

namespace RecyclingGame {

    Mesh AssetFetcher::meshFromOBJ(const char* path) {

        FILE* file = fopen(path, "r");

        if (!file) {
            Logger::error("Failed to open file: " + std::string(path));
            return {};
        }

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<Vector3> data_vertices, data_normals;
        std::vector<Vector2> data_uvs;

        while (!feof(file)) {

            char lineType[128] = {};
            fscanf(file, "%s", lineType);

            if (lineType[sizeof(lineType) - 1] != 0) {
                Logger::error("Possible buffer overflow reading OBJ. Returning");
                return {};
            }

            if (strcmp(lineType, "v") == 0) {
                Logger::info("v");
                Vector3& vertex = data_vertices.emplace_back();
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            } else if (strcmp(lineType, "vt") == 0) {
                Logger::info("vt");
                Vector2& uv = data_uvs.emplace_back();
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
            } else if (strcmp(lineType, "vn") == 0) {
                Logger::info("vn");
                Vector3& normal = data_normals.emplace_back();
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            } else if (strcmp(lineType, "f") == 0) {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                
                if (matches != 9) {
                    Logger::error("Failed to read OBJ file (possibly because the file uses quads). Returning");
                    return {};
                }

                vertexIndices.push_back(vertexIndex[0] - 1);
                vertexIndices.push_back(vertexIndex[1] - 1);
                vertexIndices.push_back(vertexIndex[2] - 1);
                
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        std::vector<Vector3> normals;
        std::vector<Vector2> uvs;
        
        for (unsigned int uvIndex : uvIndices) {
            uvs.emplace_back(data_uvs[uvIndex - 1]);
        }
        for (unsigned int normalIndex : normalIndices) {
            normals.emplace_back(data_normals[normalIndex - 1]);
        }

        Mesh result;
        result.setVertices(reinterpret_cast<float*>(data_vertices.data()), data_vertices.size());
        result.setIndices(vertexIndices.data(), vertexIndices.size());

        VertexBuffer uvBuffer;
        uvBuffer.setData(uvs.data(), uvs.size());

        VertexBuffer normalBuffer;
        normalBuffer.setData(normals.data(), normals.size());

        result.setBuffer(1, uvBuffer, BufferLayout::ElementType::FLOAT2);
        result.setBuffer(2, normalBuffer, BufferLayout::ElementType::FLOAT3);

        return result;
    }

    Texture AssetFetcher::textureFromFile(const char* path) {
        int width, height;
        unsigned char* data = stbi_load(path, &width, &height, nullptr, 4);

        if (!data) {
            Logger::error("Failed to load texture from file: " + std::string(path));
            return {};
        }
        
        Texture texture(reinterpret_cast<char*>(data), static_cast<unsigned int>(width), static_cast<unsigned int>(height));
        stbi_image_free(data);
        return texture;
    }
    
}
