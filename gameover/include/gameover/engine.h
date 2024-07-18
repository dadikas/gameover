#pragma once
#include "core/window.h"

namespace gameover
{
    class Engine
    {
    public:
        static Engine& Instance();
        ~Engine(){};
        
        [[nodiscard]] bool Initialize();
        void Shutdown();

    private:
        void GetInfo();

    private:
        core::Window mWindow;
        Engine();
        static Engine* mInstance;
    };
    
}