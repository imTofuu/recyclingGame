#include "ShaderProgram.h"

#include <glad/gl.h>

#include "Logger.h"
#include "Shader.h"

namespace RecyclingGame {

    // Generate a handle for a shader program
    ShaderProgram::ShaderProgram() {
        m_handle = glCreateProgram();
        Logger::checkForGlError("Creating shader program");
    }

    // Delete the shader program when it is no longer needed
    void ShaderProgram::remove() {
        glDeleteProgram(m_handle);
    }


    // Attach a shader and relink all shaders in the program
    void ShaderProgram::addShader(const Shader& shader) {
        glAttachShader(m_handle, shader.m_handle);
        Logger::checkForGlError("Attaching shader to program");
        glLinkProgram(m_handle);
        Logger::checkForGlError("Linking shader program");
        GLint linked = 0;
        glGetProgramiv(m_handle, GL_LINK_STATUS, &linked);
        if (!linked) {
            GLint length = 0;
            glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);
            char* log = new char[length];
            glGetProgramInfoLog(m_handle, length, nullptr, log);
            Logger::fatal(log);
            delete[] log;
        }
    }

    // Use the program for all draw calls until another program is used
    void ShaderProgram::use() {
        glUseProgram(m_handle);
        Logger::checkForGlError("Using shader program");
    }

}
