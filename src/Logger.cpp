#include "Logger.h"

#include <csignal>
#include <iostream>

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
    
}
