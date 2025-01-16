#pragma once

#include "gameover/core/window.h"

namespace gameover {
	class App {
	public:
		App(){}
		~App(){}

		virtual core::WindowProperties GetWindowProperties() { return core::WindowProperties(); }

		virtual void Initialize(){}
		virtual void Shutdown(){}

		virtual void Update(){}
		virtual void Render(){}
		virtual void ImguiRender(){}

	private:
	};
}