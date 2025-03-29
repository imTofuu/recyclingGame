#include "VertexBuffer.h"

#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    // Generate a handle for a vertex buffer and put data on GPU memory
    VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &m_handle);
        Logger::checkForGlError("Genning vertex buffer");
        setData(data, size);
    }

    // Mark the buffer for deletion
    void VertexBuffer::remove() {
        glDeleteBuffers(1, &m_handle);
        Logger::checkForGlError("Deleting vertex buffer");
    }

    // Bind the buffer and allocate memory for the data
    void VertexBuffer::setData(const void *data, unsigned int size) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        Logger::checkForGlError("Setting vertex buffer data");
    }

    // Bind the buffer to GL_ARRAY_BUFFER, the buffer target generally used for vertex data
    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        Logger::checkForGlError("Binding vertex buffer");
    }


    
}
