#include "ElementBuffer.h"

#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    // Generate a handle for an element buffer and put data on GPU memory
    ElementBuffer::ElementBuffer(const void *data, unsigned int size) {
        glGenBuffers(1, &m_handle);
        Logger::checkForGlError("Creating element buffer");
        setData(data, size);
    }

    // Mark the buffer for deletion
    void ElementBuffer::remove() {
        glDeleteBuffers(1, &m_handle);
        Logger::checkForGlError("Deleting element buffer");
    }

    // Bind the buffer and allocate memory for the data
    void ElementBuffer::setData(const void *data, unsigned int size) {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        Logger::checkForGlError("Setting element buffer data");
    }

    // Bind the buffer to GL_ELEMENT_ARRAY_BUFFER, the buffer target used for index data
    void ElementBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
        Logger::checkForGlError("Binding element buffer");
    }
    
}
