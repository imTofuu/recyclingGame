#include "ShaderProgram.h"

#include <glad/gl.h>
#include "Shader.h"

namespace RecyclingGame {

    ShaderProgram::ShaderProgram() {
        m_handle = glCreateProgram();
    }

    void ShaderProgram::addShader(const Shader& shader) {
        glAttachShader(m_handle, shader.m_handle);
        glLinkProgram(m_handle);
    }

    void ShaderProgram::use() {
        glUseProgram(m_handle);
    }

}
