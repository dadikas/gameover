#include "gameover/core/opengl_window.h"

#include "gameover/app.h"
#include "gameover/log.h"

#include "gameover/graphics/framebuffer.h"
#include "gameover/engine.h"

#include "sdl2/SDL.h"
#include "glad/glad.h"

#include "gameover/input/mouse.h"
#include "gameover/input/keyboard.h"
#include "gameover/input/joystick.h"

namespace gameover::core
{
    WindowProperties::WindowProperties() {
		title = "GAME OVER";
        x = SDL_WINDOWPOS_CENTERED;
        y = SDL_WINDOWPOS_CENTERED;

        w = 800;
        h = 600;
        wMin = 320;
        hMin = 180;

        flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
        ccR = static_cast<float>(0x64) / static_cast<float>(0xFF);
        ccG = static_cast<float>(0x95) / static_cast<float>(0xFF);
        ccB = static_cast<float>(0xED) / static_cast<float>(0xFF);
        ccA = 1.0;
    }
    OpenGlWindow::OpenGlWindow() : mWindow(nullptr), mGLContext(nullptr)
    {
    }
    OpenGlWindow::~OpenGlWindow()
    {
        Shutdown();
    }

    bool OpenGlWindow::Create(const WindowProperties& props)
    {
                
        mWindow = SDL_CreateWindow(props.title.c_str(), props.x, props.y, props.w, props.h, props.flags);
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
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        // Set window size
        SDL_SetWindowMinimumSize(mWindow, props.wMin, props.hMin);

        // Create OpenGL context
        mGLContext = SDL_GL_CreateContext(mWindow);
        if (mGLContext == nullptr)
        {
            GAMEOVER_ERROR("Error creating context: {}", SDL_GetError());
            return false;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        //Engine::Instance().GetRenderManager().SetClearColor(props.ccR, props.ccG, props.ccB, 1.f);
        mFramebuffer = std::make_shared<graphics::Framebuffer>(props.w, props.h);
        mFramebuffer->SetClearColour(props.ccR, props.ccG, props.ccB, 1.f);

        mImguiWindow.Create(props.imguiProps);
        return true;
    }

    // Shutdown: Clean up window and context
    void OpenGlWindow::Shutdown()
    {
		if (mGLContext)
		{
			SDL_GL_DeleteContext(mGLContext);
            mGLContext = nullptr;
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
            case SDL_CONTROLLERDEVICEREMOVED:
                input::Joystick::OnJoystickDisconnected(event.cdevice);

            default:
                break;
            }
            mImguiWindow.HandlSDLEvent(event);
        }
        //update input
        if (!mImguiWindow.WantCaptureMouse()) {
			input::Mouse::Update();
        }
        if (!mImguiWindow.WantCaptureKeyboard()) {
            input::Keyboard::Update();
        }
        input::Joystick::Update();
    }

    void OpenGlWindow::GetSize(int& w, int& h)
    {
        SDL_GetWindowSize(mWindow, &w, &h);
    }

    // Begin rendering (clear buffers)
    void OpenGlWindow::BeginRender()
    {
        /*Engine::Instance().GetRenderManager().Clear();
        auto cmd = std::make_unique<graphics::rendercommands::PushFramebuffer>(mFramebuffer);
		Engine::Instance().GetRenderManager().Submit(std::move(cmd));*/

        auto& rm = Engine::Instance().GetRenderManager();
        rm.Clear();
        rm.Submit(GAMEOVER_SUBMIT_RC(PushFramebuffer, mFramebuffer));
    }

    // End rendering (swap buffers)
    void OpenGlWindow::EndRender()
    {
		auto& rm = Engine::Instance().GetRenderManager();
		rm.Submit(GAMEOVER_SUBMIT_RC(PopFramebuffer));
        rm.Flush();

        mImguiWindow.BeginRender();
        Engine::Instance().GetApp().ImguiRender();
        mImguiWindow.EndRender();

        SDL_GL_SwapWindow(mWindow);
    }
}
