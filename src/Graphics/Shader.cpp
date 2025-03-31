#include "Shader.h"

#include <fstream>
#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {
    
    Shader::Shader(const char* path, ShaderType type) {
        // Create the Input File Stream to read the shader source from path
        std::ifstream file(path, std::ios::in);
        if (!file.is_open()) {
            Logger::error("Failed to open shader file: " + std::string(path));
            return;
        }
        std::string source;
        std::string line;
        // Get the next line and concatenate it to source until the end of the file
        while (std::getline(file, line)) {
            source += line += '\n';
        }

        const char* sourcePointer = source.c_str();

        // Generate the shader handle
        m_handle = glCreateShader(shaderType(type));
        Logger::checkForGlError("Creating shader");

        // Set the source of the shader to the file source and compile it
        glShaderSource(m_handle, 1, &sourcePointer, nullptr);
        Logger::checkForGlError("Setting shader source");
        glCompileShader(m_handle);
        Logger::checkForGlError("Compiling shader");

        // Check for compilation success and log errors
        int success;
        glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(m_handle, 512, nullptr, infoLog);
            Logger::error("Vertex Shader compilation failed: " + std::string(infoLog));
        }
    }

    // Mark the shader for deletion
    void Shader::remove() {
        glDeleteShader(m_handle);
        Logger::checkForGlError("Deleting shader");
    }

    // Helper function to get data for glCreateShader so glad symbols don't have to be exposed
    // in the header file, which can lead to include conflicts
    constexpr unsigned int Shader::shaderType(ShaderType type) {
        switch (type) {
            case ShaderType::VERT:
                return GL_VERTEX_SHADER;
            case ShaderType::FRAG:
                return GL_FRAGMENT_SHADER;
        }
        return 0;
    }
    
}
