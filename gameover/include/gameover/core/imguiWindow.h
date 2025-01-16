#pragma once
typedef union SDL_Event SDL_Event;
namespace gameover::core {

	struct ImguiWindowProperties {
		bool MoveFromTitleBarOnly = true;
		bool IsDockingEnable = false;
		bool IsViewportEnable = false;

	};

	class ImGuiWindow {
	public:
		ImGuiWindow(){}
		~ImGuiWindow(){}

		void Create(const ImguiWindowProperties& props);
		void Shutdown();

		void HandlSDLEvent(SDL_Event& e);

		bool WantCaptureMouse();
		bool WantCaptureKeyboard();

		void BeginRender();
		void EndRender();


	private:


	};
}