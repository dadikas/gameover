#pragma once
#include "window.h"
struct SDL_Window;
using SDL_GLContext = void*;
namespace gameover::core
{
    class OpenGlWindow : public Window
    {
    public:

        OpenGlWindow();
        ~OpenGlWindow();

        bool Create() override;
        void Shutdown() override;
        void PumpEvents() override;

        void BeginRender() override;
        void EndRender() override;
     private:
        SDL_Window* mWindow;
        SDL_GLContext mContext;
    };
};
