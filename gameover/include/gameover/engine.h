#pragma once
#include "core/window.h"
#include "managers/logmanager.h"
namespace gameover
{
    class Engine
    {
    public:
        static Engine& Instance();
        ~Engine(){};
        
        void Run();
        inline void Quit(){ mIsRunning = false; } 
        
    private:
        void GetInfo();
         [[nodiscard]] bool Initialize();
        void Shutdown();

    private:
        bool mIsRunning;
        bool mIsInitialized;

        core::Window* mWindow;
        managers::LogManager mLogManager;


        Engine();
        static Engine* mInstance;
    };
    
}