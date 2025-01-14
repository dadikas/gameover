#include "gameover/core/opengl_window.h"
#include "gameover/log.h"
#include "gameover/engine.h"
#include "sdl2/SDL.h"
#include "glad/glad.h"

#include "gameover/input/mouse.h"
#include "gameover/input/keyboard.h"
#include "gameover/input/joystick.h"

namespace gameover::core
{
    OpenGlWindow::OpenGlWindow() : mWindow(nullptr), mContext(nullptr)
    {
    }
    OpenGlWindow::~OpenGlWindow()
    {
        Shutdown();
    }

    bool OpenGlWindow::Create()
    {

        bool ret = true;
        
        mWindow = SDL_CreateWindow("Gameover", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if (!mWindow)
        {
            GAMEOVER_ERROR("Error creating window: {}", SDL_GetError());
            return false;
        }

        // Set OpenGL context attributes
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Set window size
        SDL_SetWindowSize(mWindow, 800, 600);

        // Create OpenGL context
        mContext = SDL_GL_CreateContext(mWindow);
        if (mContext == nullptr)
        {
            GAMEOVER_ERROR("Error creating context: {}", SDL_GetError());
            return false;
        }

        // Load OpenGL functions using glad
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            GAMEOVER_ERROR("Failed to initialize OpenGL loader!");
            return false;
        }


        // Set clear color (light blue)
       
        return ret;
    }

    // Shutdown: Clean up window and context
    void OpenGlWindow::Shutdown()
    {
		if (mContext)
		{
			SDL_GL_DeleteContext(mContext);
			mContext = nullptr;
		}

		if (mWindow)
		{
			SDL_DestroyWindow(mWindow);
			mWindow = nullptr;
		}
    }

    // Pump events (handle SDL events)
    void OpenGlWindow::PumpEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Engine::Instance().Quit();
                break;
            case SDL_CONTROLLERDEVICEADDED:
                input::Joystick::OnJoystickConnected(event.cdevice);
                break;
            default:
                break;
            }
        }
        //update input
        input::Mouse::Update();
        input::Keyboard::Update();
    }

    void OpenGlWindow::GetSize(int& w, int& h)
    {
        SDL_GetWindowSize(mWindow, &w, &h);
    }

    // Begin rendering (clear buffers)
    void OpenGlWindow::BeginRender()
    {
        Engine::Instance().GetRenderManager().Clear();
    }

    // End rendering (swap buffers)
    void OpenGlWindow::EndRender()
    {
        SDL_GL_SwapWindow(mWindow);
    }
}
