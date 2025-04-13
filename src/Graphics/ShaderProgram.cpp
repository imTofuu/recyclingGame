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

    int ShaderProgram::getUniformLocation(const char *name) const {
        int location = glGetUniformLocation(m_handle, name);
        Logger::checkForGlError("Getting uniform location");
        if (location == -1) {
            Logger::error("Uniform not found");
        }
        return location;
    }


    void ShaderProgram::setByte(const char* name, char value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting byte uniform");
    }

    void ShaderProgram::setUByte(const char* name, unsigned char value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting unsigned byte uniform");
    }

    void ShaderProgram::setShort(const char* name, short value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting short uniform");
    }

    void ShaderProgram::setUShort(const char* name, unsigned short value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting unsigned short uniform");
    }

    void ShaderProgram::setInt(const char* name, int value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting int uniform");
    }

    void ShaderProgram::setUInt(const char* name, unsigned int value) {
        use();
        glUniform1i(getUniformLocation(name), value);
        Logger::checkForGlError("Setting unsigned int uniform");
    }

    void ShaderProgram::setFloat(const char* name, float value) {
        use();
        glUniform1f(getUniformLocation(name), value);
        Logger::checkForGlError("Setting float uniform");
    }

    void ShaderProgram::setDouble(const char* name, double value) {
        use();
        glUniform1d(getUniformLocation(name), value);
        Logger::checkForGlError("Setting double uniform");
    }

    void ShaderProgram::setMat2(const char* name, const float* value) {
        use();
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat2 uniform");
    }

    void ShaderProgram::setDMat2(const char* name, const double* value) {
        use();
        glUniformMatrix2dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat2 uniform");
    }

    void ShaderProgram::setMat2x3(const char* name, const float* value) {
        use();
        glUniformMatrix2x3fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat2x3 uniform");
    }

    void ShaderProgram::setDMat2x3(const char* name, const double* value) {
        use();
        glUniformMatrix2x3dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat2x3 uniform");
    }

    void ShaderProgram::setMat2x4(const char* name, const float* value) {
        use();
        glUniformMatrix2x4fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat2x4 uniform");
    }

    void ShaderProgram::setDMat2x4(const char* name, const double* value) {
        use();
        glUniformMatrix2x4dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat2x4 uniform");
    }

    void ShaderProgram::setMat3(const char* name, const float* value) {
        use();
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat3 uniform");
    }

    void ShaderProgram::setDMat3(const char* name, const double* value) {
        use();
        glUniformMatrix3dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat3 uniform");
    }

    void ShaderProgram::setMat3x2(const char* name, const float* value) {
        use();
        glUniformMatrix3x2fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat3x2 uniform");
    }

    void ShaderProgram::setDMat3x2(const char* name, const double* value) {
        use();
        glUniformMatrix3x2dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat3x2 uniform");
    }

    void ShaderProgram::setMat3x4(const char* name, const float* value) {
        use();
        glUniformMatrix3x4fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat3x4 uniform");
    }

    void ShaderProgram::setDMat3x4(const char* name, const double* value) {
        use();
        glUniformMatrix3x4dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat3x4 uniform");
    }

    void ShaderProgram::setMat4(const char* name, const float* value) {
        use();
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat4 uniform");
    }

    void ShaderProgram::setDMat4(const char* name, const double* value) {
        use();
        glUniformMatrix4dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat4 uniform");
    }

    void ShaderProgram::setMat4x2(const char* name, const float* value) {
        use();
        glUniformMatrix4x2fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat4x2 uniform");
    }

    void ShaderProgram::setDMat4x2(const char* name, const double* value) {
        use();
        glUniformMatrix4x2dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat4x2 uniform");
    }

    void ShaderProgram::setMat4x3(const char* name, const float* value) {
        use();
        glUniformMatrix4x3fv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting mat4x3 uniform");
    }

    void ShaderProgram::setDMat4x3(const char* name, const double* value) {
        use();
        glUniformMatrix4x3dv(getUniformLocation(name), 1, GL_FALSE, value);
        Logger::checkForGlError("Setting dmat4x3 uniform");
    }

    void ShaderProgram::setBytes(const char* name, const char* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setBytes");
        }
        Logger::checkForGlError("Setting byte uniform");
    }

    void ShaderProgram::setUBytes(const char* name, const unsigned char* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setUBytes");
        }
        Logger::checkForGlError("Setting unsigned byte uniform");
    }

    void ShaderProgram::setShorts(const char* name, const short* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setShorts");
        }
        Logger::checkForGlError("Setting short uniform");
    }

    void ShaderProgram::setUShorts(const char* name, const unsigned short* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setUShorts");
        }
        Logger::checkForGlError("Setting unsigned short uniform");
    }

    void ShaderProgram::setInts(const char* name, const int* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setInts");
        }
        Logger::checkForGlError("Setting int uniform");
    }

    void ShaderProgram::setUInts(const char* name, const unsigned int* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const int*>(value);

        switch (num) {
            case 1:
                glUniform1iv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2iv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3iv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4iv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setUInts");
        }
        Logger::checkForGlError("Setting unsigned int uniform");
    }

    void ShaderProgram::setFloats(const char* name, const float* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const float*>(value);

        switch (num) {
            case 1:
                glUniform1fv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2fv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3fv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4fv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setFloats");
        }
        Logger::checkForGlError("Setting float uniform");
    }

    void ShaderProgram::setDoubles(const char* name, const double* value, unsigned int num) {
        use();

        int location = getUniformLocation(name);
        auto ptrvalue = reinterpret_cast<const double*>(value);

        switch (num) {
            case 1:
                glUniform1dv(location, 1, ptrvalue);
                break;
            case 2:
                glUniform2dv(location, 1, ptrvalue);
                break;
            case 3:
                glUniform3dv(location, 1, ptrvalue);
                break;
            case 4:
                glUniform4dv(location, 1, ptrvalue);
                break;
            default:
                Logger::error("Invalid num for setDoubles");
        }
        Logger::checkForGlError("Setting double uniform");
    }

}
