#pragma once

#include "Mesh.h"
#include <vector>

namespace RecyclingGame {

    class Model {
    public:

        void addMesh(const Mesh& mesh) { m_meshes.push_back(mesh); }
        void setTexture(unsigned int index, const Texture& texture) { m_meshes.at(index).setTexture(texture); }

        void draw();

    private:

        std::vector<Mesh> m_meshes;
        
    };
    
}