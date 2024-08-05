#pragma once

namespace gameover::managers
{

    class LogManager
    {
    public:
        LogManager() = default;
        ~LogManager() = default;

        void Initialize();
        void Shutdown();
    };
}