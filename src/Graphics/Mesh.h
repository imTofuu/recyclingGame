#pragma once

#include <vector>

#include "ElementBuffer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace RecyclingGame {

    class Mesh {
    public:

        Mesh();
        
        void remove();

        void setVertices(const float* vertices, unsigned int numVertices);
        void setIndices(const unsigned int* indices, unsigned int numIndices);

        void setBuffer(unsigned int index, VertexBuffer& buffer, BufferLayout::ElementType type);
        void setTexture(const Texture& texture) { m_texture = texture; }
        
        void bind();

        [[nodiscard]] unsigned int getNumVertices() const { return m_elementBuffer.hasExisted() ? m_numIndices : m_numVertices; }

    private:

        VertexBuffer m_vertexBuffer;
        std::vector<VertexBuffer> m_buffers;

        unsigned int m_numVertices = 0;
        unsigned int m_numIndices = 0;
        
        ElementBuffer m_elementBuffer;

        Texture m_texture;

        VertexArray m_vertexArray;
        
    };
    
}