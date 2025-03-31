#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

namespace RecyclingGame {

    class AssetFetcher {
    public:

        static Mesh meshFromOBJ(const char* path);
        static Texture textureFromFile(const char* path);
        
    };
    
}
