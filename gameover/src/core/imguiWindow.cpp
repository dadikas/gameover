#include "gameover/core/imguiWindow.h"

#include "gameover/engine.h"

#include "sdl2/SDL.h"

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_sdl2.h"
#include "external/imgui/imgui_impl_opengl3.h"

namespace gameover::core {


	void ImGuiWindow::Create(const ImguiWindowProperties& props) {
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigWindowsMoveFromTitleBarOnly = props.MoveFromTitleBarOnly;
		if (props.IsDockingEnable){
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		}
		if (props.IsViewportEnable){
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		}

		auto& window = Engine::Instance().GetWindow();
		ImGui_ImplSDL2_InitForOpenGL(window->GetSDLWindow(), window->GetGLContext());
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiWindow::Shutdown() {

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiWindow::HandlSDLEvent(SDL_Event& e) {

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	void ImGuiWindow::BeginRender() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiWindow::EndRender() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			auto& window = Engine::Instance().GetWindow();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			SDL_GL_MakeCurrent(window->GetSDLWindow(), window->GetGLContext());
		}
	}

	bool ImGuiWindow::WantCaptureMouse()
	{
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImGuiWindow::WantCaptureKeyboard()
	{
		return ImGui::GetIO().WantCaptureKeyboard;
	}

}