#include "ShaderProgram.h"

#include <glad/gl.h>
#include "Shader.h"

namespace RecyclingGame {

    // Generate a handle for a shader program
    ShaderProgram::ShaderProgram() {
        m_handle = glCreateProgram();
    }

    // Attach a shader and relink all shaders in the program
    void ShaderProgram::addShader(const Shader& shader) {
        glAttachShader(m_handle, shader.m_handle);
        glLinkProgram(m_handle);
    }

    // Use the program for all draw calls until another program is used
    void ShaderProgram::use() {
        glUseProgram(m_handle);
    }

}
