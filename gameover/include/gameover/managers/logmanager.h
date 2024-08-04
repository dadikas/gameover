#pragma once

namespace gameover::manager{

    class LogManager
    {
    public:
        LogManager() = default;
        ~LogManager() = default;

        void Initialize();
        void Shutdown();
    };
}