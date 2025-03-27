#include "VertexBuffer.h"

#include <glad/gl.h>

namespace RecyclingGame {

    // Generate a handle for a vertex buffer and put data on GPU memory
    VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &m_handle);
        setData(data, size);
    }

    // Mark the buffer for deletion
    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_handle);
    }

    // Bind the buffer and allocate memory for the data
    void VertexBuffer::setData(const void *data, unsigned int size) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    // Bind the buffer to GL_ARRAY_BUFFER, the buffer target generally used for vertex data
    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    }


    
}