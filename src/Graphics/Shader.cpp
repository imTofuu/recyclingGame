#include "Shader.h"

#include <fstream>
#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    Shader::Shader(const char* path, ShaderType type) {
        std::ifstream file(path, std::ios::in);
        if (!file.is_open()) {
            Logger::error((std::string("Failed to open shader file: ") + std::string(path)).c_str());
            return;
        }
        std::string source;
        std::string line;
        while (std::getline(file, line)) {
            source += line += '\n';
        }

        const char* sourcePointer = source.c_str();

        m_handle = glCreateShader(shaderType(type));
        glShaderSource(m_handle, 1, &sourcePointer, nullptr);
        glCompileShader(m_handle);

        int success;
        glGetShaderiv(m_handle, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(m_handle, 512, nullptr, infoLog);
            Logger::fatal(("Vertex Shader compilation failed: " + std::string(infoLog)).c_str());
        }
    }

    Shader::~Shader() {
        glDeleteShader(m_handle);
    }

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
