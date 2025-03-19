#pragma once

namespace RecyclingGame {
    class Logger {
    public:

        static void info(const char* msg);
        static void error(const char* msg);
        static void fatal(const char* msg);
    
    };
}