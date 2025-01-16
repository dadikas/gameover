#pragma once

#include "gameover/core/imguiWindow.h"

#include <string>

struct SDL_Window;
using SDL_GLContext = void*;
namespace gameover::graphics {
	class Framebuffer;
}
namespace gameover::core
{
	struct WindowProperties {
		std::string title;
		int x, y, w, h;
		int wMin, hMin;
		int flags;
		float ccR, ccG, ccB, ccA;
        ImguiWindowProperties imguiProps;

		WindowProperties();
	};
    class Window
    {
    public:
        virtual bool Create(const WindowProperties& props);
        virtual void Shutdown();
        virtual void PumpEvents();

        virtual void GetSize(int& w, int& h);

        virtual inline SDL_Window* GetSDLWindow() { return nullptr; };
		virtual inline SDL_GLContext GetGLContext() { return nullptr; };
        virtual inline graphics::Framebuffer* GetFramebuffer() { return nullptr; };

        virtual void BeginRender();
        virtual void EndRender();

        virtual ~Window() = default;
    };


}