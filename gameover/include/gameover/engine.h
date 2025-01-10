#pragma once
#include "core/window.h"
#include "managers/logmanager.h"
#include "managers/rendermanager.h"
namespace gameover
{
    class Engine
    {
    public:
        static Engine& Instance();
        ~Engine(){};
        
        void Run();
        inline void Quit(){ mIsRunning = false; } 

        inline managers::RenderManager& GetRenderManager() {
            return mRendermanager;
        }
        
    private:
        void GetInfo();
         [[nodiscard]] bool Initialize();
        void Shutdown();

    private:
        bool mIsRunning;
        bool mIsInitialized;

        core::Window* mWindow;

        managers::LogManager mLogManager;
        managers::RenderManager mRendermanager;


        Engine();
        static Engine* mInstance;
    };
    
}