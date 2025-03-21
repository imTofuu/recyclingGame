#include "VertexBuffer.h"

#include <glad/gl.h>

namespace RecyclingGame {

    VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
        glGenBuffers(1, &m_handle);
        setData(data, size);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_handle);
    }

    void VertexBuffer::setData(const void *data, unsigned int size) {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    }


    
}