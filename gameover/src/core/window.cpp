#include "core/window.h"
#include "engine.h"
#include "sdl2/SDL.h"
#include "log.h"

#include "glad/glad.h"

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
        mWindow = SDL_CreateWindow("Gameover", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!mWindow)
        {
           GAMEOVER_ERROR("Error creating window: {}", SDL_GetError() );
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        SDL_SetWindowSize(mWindow, 400, 400);

        mContext = SDL_GL_CreateContext(mWindow);
        if (mContext == nullptr)
        {
            GAMEOVER_ERROR("Error creating context: {}", SDL_GetError());
            return false;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

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

    void Window::BeginRender()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Window::EndRender()
    {
        SDL_GL_SwapWindow(mWindow);
    }
}