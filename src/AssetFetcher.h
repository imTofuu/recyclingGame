#pragma once

#include <assimp/scene.h>

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Texture.h"

namespace RecyclingGame {

    class AssetFetcher {
    public:

        static Model modelFromPath(const char* path);
        static Texture textureFromFile(const char* path);

        static Model getLightModel() { return *m_lightModel; }

    private:
        static Model* m_lightModel;

        static void processModelNode(Model& model, aiNode* node, const aiScene* scene);
        static Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        friend class Game;
        
    };
    
}
