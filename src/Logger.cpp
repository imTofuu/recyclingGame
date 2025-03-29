#include "Logger.h"

#include <csignal>
#include <iostream>
#include <glad/gl.h>

namespace RecyclingGame {

    // Log a message to std::cout. This should be used
    // to give non-essential info to the user through
    // the console.
    void Logger::info(const char* msg) {
        std::cout << msg << std::endl;
    }

    // Log a message to std::cerr. This should be used
    // when something goes wrong but it is recoverable.
    void Logger::error(const char* msg) {
        std::cerr << msg << std::endl;
    }

    // Log a message to std::cerr and create a breakpoint
    // for debugging. This should be used when an error is
    // unrecoverable.
    void Logger::fatal(const char* msg) {
        std::cerr << msg << std::endl;
        raise(SIGABRT);
    }

    // Check for a GL error. This is called after most OpenGL
    // calls to check if something went wrong.
    void Logger::checkForGlError(const char* msg) {
        unsigned int error = glGetError();
        if (error == GL_NO_ERROR) return;
        
        const char* errorm = nullptr;
        switch (error) {
            case GL_INVALID_ENUM:
                errorm = "GL_INVALID_ENUM";
            break;
            case GL_INVALID_VALUE:
                errorm = "GL_INVALID_VALUE";
            break;
            case GL_INVALID_OPERATION:
                errorm = "GL_INVALID_OPERATION";
            break;
            case GL_OUT_OF_MEMORY:
                errorm = "GL_OUT_OF_MEMORY";
            break;
            default:
                errorm = "Unknown error";
        }
        std::cerr << msg << " (" << errorm << ") " << std::endl;
        raise(SIGABRT);
        while (error != GL_NO_ERROR) {
            error = glGetError();
        }
    }
    
}
