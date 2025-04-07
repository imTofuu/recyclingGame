#include "Model.h"

#include <glad/gl.h>

namespace RecyclingGame {

    void Model::draw() {
        for (auto& mesh : m_meshes) {
            mesh.bind();

            glDrawElements(GL_TRIANGLES, mesh.getNumVertices(), GL_UNSIGNED_INT, nullptr);
        }
    }

    
}