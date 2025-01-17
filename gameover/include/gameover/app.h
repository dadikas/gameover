#pragma once

#include "gameover/core/window.h"

namespace gameover {
	class _declspec(dllexport) App {
	public:
		App(){}
		virtual ~App(){}

		virtual core::WindowProperties GetWindowProperties() { return core::WindowProperties(); }

		virtual void Initialize(){}
		virtual void Shutdown(){}

		virtual void Update(){}
		virtual void Render(){}
		virtual void ImguiRender(){}

	private:
	};
	App* CreateApp();
}