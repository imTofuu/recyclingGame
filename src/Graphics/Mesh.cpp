#include "Mesh.h"

namespace RecyclingGame {

    Mesh::Mesh() {
        setBuffer(0, m_vertexBuffer, BufferLayout::ElementType::FLOAT3);
    }

    void Mesh::remove() {
        m_vertexBuffer.remove();
        m_vertexArray.remove();
        m_elementBuffer.remove();
        for (auto& buffer : m_buffers) {
            buffer.remove();
        }
    }
    
    void Mesh::setVertices(const float* vertices, unsigned int numVertices) {
        m_vertexBuffer.setData(vertices, numVertices * sizeof(float) * 3);
        m_numVertices = numVertices;
    }

    void Mesh::setIndices(const unsigned int* indices, unsigned int numIndices) {
        m_elementBuffer.setData(indices, numIndices * sizeof(unsigned int));
        m_numIndices = numIndices;
    }

    void Mesh::setBuffer(unsigned int index, VertexBuffer& buffer, BufferLayout::ElementType type) {
        m_vertexArray.setBuffer(index, buffer, type);
    }

    void Mesh::bind() {
        m_vertexArray.bind();
        m_elementBuffer.bind();
    }

    
}