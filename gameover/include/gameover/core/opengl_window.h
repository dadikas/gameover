#pragma once
#include "window.h"
#include "gameover/core/imguiWindow.h"

#include <memory>

namespace gameover::core
{
	struct WindowProperties;
    class OpenGlWindow : public Window
    {
    public:

        OpenGlWindow();
        ~OpenGlWindow();

        bool Create(const WindowProperties& props) override;
        void Shutdown() override;
        void PumpEvents() override;

        inline SDL_Window* GetSDLWindow() override { return mWindow; };
        inline SDL_GLContext GetGLContext() override { return mGLContext; };
        inline graphics::Framebuffer* GetFramebuffer() override { return mFramebuffer.get(); };

        void GetSize(int& x, int& y) override;

        void BeginRender() override;
        void EndRender() override;
     private:
        SDL_Window* mWindow;
        SDL_GLContext mGLContext;
        ImGuiWindow mImguiWindow;
        std::shared_ptr<graphics::Framebuffer> mFramebuffer;
    };
};
