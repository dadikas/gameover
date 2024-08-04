#include "core/window.h"
#include "engine.h"
#include "sdl2/SDL.h"
#include <iostream>

namespace gameover::core
{
    Window::Window() : mWindow(nullptr)
    {
    }
    Window::~Window()
    {
        Shutdown();
    }
    bool Window::Create()
    {
        bool ret = true;
        mWindow = SDL_CreateWindow("Gameover", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
        if (!mWindow)
        {
            std::cout << "Error creating window " << SDL_GetError() << std::endl;
        }
        return ret;
    }
    void Window::Shutdown()
    {
        if (mWindow)
        {
            SDL_DestroyWindow(mWindow);
            mWindow = nullptr;
        }
    }
    void Window::PumpEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;

            default:
                break;
            }
        }
    }
}