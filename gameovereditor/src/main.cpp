#include <iostream>
#include "gameover/engine.h"
#include "gameover/app.h"
#include "gameover/main.h"
#include "gameover/log.h"

#include "gameover/core/opengl_window.h"

#include "gameover/graphics/mesh.h"
#include "gameover/graphics/shader.h"
#include "gameover/graphics/framebuffer.h"

#include "gameover/input/mouse.h"
#include "gameover/input/keyboard.h"
#include "gameover/input/joystick.h"

#include "external/imgui/imgui.h"

using namespace gameover;

class Editor : public gameover::App {
private:
	std::shared_ptr<graphics::Mesh> mMesh;
	std::shared_ptr<graphics::Shader> mShader;
public:

	core::WindowProperties GetWindowProperties() {
		core::WindowProperties props;

		props.title = "GameoverEditor";
		props.w = 800;
		props.h = 600;

		props.imguiProps.IsDockingEnable = true;

		return props;
	}

    void Initialize() override {

		float vertices[]{
				 0.5f,	 0.5f,	0.f,
				 0.5f,	 -0.5f,	0.f,
				 -0.5f,	 -0.5f,	0.f,
				 -0.5f,	 0.5f,	0.f,
		};
		uint32_t elements[]{
			0,3,1,
			1,3,2
		};
		mMesh = std::make_shared<graphics::Mesh>(&vertices[0], 4, 3, &elements[0], 6);

		const char* vertextShader = R"(
				#version 410 core
				layout (location = 0) in vec3 position;
				out vec3 vpos;
				uniform vec2 offset = vec2(0.5);			
				void main(){
					vpos = position + vec3(offset, 0);
					gl_Position = vec4(position, 1.0);
				}
			)";

		const char* fragmentShader = R"(
				#version 410 core
				out vec4 outColor;
				in vec3 vpos;

				uniform vec3 color = vec3(0.0);		
		
				void main(){
					outColor = vec4(vpos,1.0);
				}
			)";
		mShader = std::make_shared<graphics::Shader>(vertextShader, fragmentShader);
		mShader->SetUniformFloat3("color", 1, 0, 0);
    }

    void Shutdown() override {

    }

    void Update() override {
		int windowW = 0;
		int windowH = 0;

		Engine::Instance().GetWindow()->GetSize(windowW, windowH);

		float xNorm = (float)input::Mouse::X() / (float)windowW;
		float yNorm = (float)input::Mouse::Y() / (float)windowH;



		mShader->SetUniformFloat2("offset", xNorm, yNorm);
    }

    void Render() override {
		auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mMesh, mShader);
		Engine::Instance().GetRenderManager().Submit(std::move(rc));
		Engine::Instance().GetRenderManager().Flush();

    }
	void ImguiRender() override {
		ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(),ImGui::GetMainViewport());
		ImGui::Begin("ReactPosx");
		ImGui::End();
		ImGui::Begin("ReactPosy");
		ImGui::End();
		if (ImGui::Begin("GameView")) {
			if (ImGui::IsWindowHovered()) {
				ImGui::SetNextFrameWantCaptureMouse(false);
			}
			auto& window = Engine::Instance().GetWindow();

			ImVec2 size = { 480,320 };
			ImVec2 uv0 = { 0,1 };
			ImVec2 uv1 = { 1,0 };
			ImGui::Image((intptr_t)window->GetFramebuffer()->GetTextureId(), size, uv0, uv1);
		}
		ImGui::End();
	}
};

gameover::App* CreateApp() {
    return new Editor();
}