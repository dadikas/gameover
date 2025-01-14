#pragma once
#include "gameover/app.h"
#include "gameover/core/window.h"
//#include "gameover/core/opengl_window.h"
#include "gameover/managers/logmanager.h"
#include "gameover/managers/rendermanager.h"
namespace gameover
{
    class App;
    class Engine
    {
    public:
        static Engine& Instance();
        ~Engine(){};
        
        void Run(App* app);
        inline void Quit(){ mIsRunning = false; } 

        inline std::shared_ptr<core::Window> GetWindow() { return mWindow; }

        inline managers::RenderManager& GetRenderManager() {
            return mRendermanager;
        }
        
    private:
        void GetInfo();
         [[nodiscard]] bool Initialize();
        void Shutdown();
        void Update();
        void Render();

    private:
        bool mIsRunning;
        bool mIsInitialized;

        std::shared_ptr<core::Window> mWindow;
        App* mApp;

        managers::LogManager mLogManager;
        managers::RenderManager mRendermanager;


        Engine();
        static Engine* mInstance;
    };
    
}