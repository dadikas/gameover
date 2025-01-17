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
#include "external/glm/glm.hpp"
#include "external/glm/gtc/type_ptr.hpp"
#include "external/glm/gtc/matrix_transform.hpp"

using namespace gameover;

class Editor : public gameover::App {
private:
	std::shared_ptr<graphics::Mesh> mMesh;
	std::shared_ptr<graphics::Shader> mShader;
	
	float xKeyOffset = 0.f;
	float yKeyOffset = 0.f;
	float keySpeed = 0.001f;

	//glm::mat4 mModelMatrix;
	glm::vec2 mRectPos, mRectSize;
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
				uniform mat4 model = mat4(1.0);			
				void main(){
					vpos = position + vec3(offset, 0);
					gl_Position = model * vec4(position, 1.0);
				}
			)";

		const char* fragmentShader = R"(
				#version 410 core
				out vec4 outColor;
				in vec3 vpos;

				uniform vec3 color = vec3(0.0);		
				uniform float blue = 0.5f;
				void main(){
					outColor = vec4(vpos.xy, blue, 1.0);
				}
			)";
		mShader = std::make_shared<graphics::Shader>(vertextShader, fragmentShader);
		mShader->SetUniformFloat3("color", 1, 0, 0);

		mRectPos = glm::vec2(0.f);
		mRectSize = glm::vec2(1.f);
    }

    void Shutdown() override {

    }

    void Update() override {

		auto windowSize = Engine::Instance().GetWindow()->GetSize();

		float xNorm = (float)input::Mouse::X() / (float)windowSize.x;
		float yNorm = (float)(windowSize.y - input::Mouse::Y()) / (float)windowSize.y ;

		if (input::Keyboard::Key(GAMEOVER_INPUT_KEY_LEFT)) { xKeyOffset -= keySpeed; }
		if (input::Keyboard::Key(GAMEOVER_INPUT_KEY_RIGHT)) { xKeyOffset += keySpeed; }
		if (input::Keyboard::Key(GAMEOVER_INPUT_KEY_UP)) { yKeyOffset -= keySpeed; }
		if (input::Keyboard::Key(GAMEOVER_INPUT_KEY_DOWN)) { yKeyOffset -= keySpeed; }

		if (input::Keyboard::KeyDown(GAMEOVER_INPUT_KEY_LEFT)) { xKeyOffset -= keySpeed * 100; }
		if (input::Keyboard::KeyDown(GAMEOVER_INPUT_KEY_RIGHT)) { xKeyOffset += keySpeed *100; }

		if (input::Joystick::IsJoystickAvailable(0)) {
			if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Left)) { xKeyOffset -= keySpeed; }
			if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Right)) { xKeyOffset += keySpeed; }
			if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Up)) { yKeyOffset += keySpeed; }
			if (input::Joystick::GetButton(0, input::Joystick::Button::DPAD_Down)) { yKeyOffset -= keySpeed; }

			float blue = input::Joystick::GetAxis(0, input::Joystick::Axis::LeftTrigger);
			mShader->SetUniformFloat1("model", blue);

		}



		mShader->SetUniformFloat2("offset", xNorm + xKeyOffset, yNorm + yKeyOffset);


		glm::mat4 model = glm::mat4(1.f);

		// Sử dụng giá trị đã được chỉnh sửa bởi ImGui::DragFloat2
		model = glm::translate(model, { mRectPos.x, mRectPos.y, 0.f });
		model = glm::scale(model, { mRectSize.x, mRectSize.y, 1.f });

		mShader->SetUniformMat4("model", model);
    }

    void Render() override {
		Engine::Instance().GetRenderManager().Submit(GAMEOVER_SUBMIT_RC(RenderMesh, mMesh, mShader));
    }
	void ImguiRender() override {
		ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(),ImGui::GetMainViewport());
		if (ImGui::Begin("Rect Pos")) {
			ImGui::DragFloat2("Rect Pos", glm::value_ptr(mRectPos), 0.01f);
			//std::cout << "Rect Pos Updated: " << mRectPos.x << ", " << mRectPos.y << std::endl;
		}
		ImGui::End();

		if (ImGui::Begin("React Size")) {
			ImGui::DragFloat2("Rect size", glm::value_ptr(mRectSize), 0.01f);
			//std::cout << "Rect Size Updated: " << mRectSize.x << ", " << mRectSize.y << std::endl;
		}
		ImGui::End();

		if (ImGui::Begin("GameView")) {
			if (ImGui::IsWindowHovered() || ImGui::IsItemActive()) {
				ImGui::SetNextFrameWantCaptureMouse(false);
				ImGui::SetNextFrameWantCaptureKeyboard(false);
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