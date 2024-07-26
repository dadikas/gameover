#pragma once

struct SDL_Window;
namespace gameover::core
{
    class Window
    {
    public:
        Window();
        ~Window();

        bool Create();
        void Shutdown();
    private:
        SDL_Window* mWindow;
    };
}