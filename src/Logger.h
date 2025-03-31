#pragma once
#include <string>

namespace RecyclingGame {
    class Logger {
    public:

        static void info(const char* msg);
        static void info(const std::string& msg) { info(msg.c_str()); }
        static void error(const char* msg);
        static void error(const std::string& msg) { error(msg.c_str()); }
        static void fatal(const char* msg);
        static void fatal(const std::string& msg) { fatal(msg.c_str()); }

        static void checkForGlError(const char* msg);
        static void checkForGlError(const std::string& msg) { checkForGlError(msg.c_str()); }
    
    };
}
