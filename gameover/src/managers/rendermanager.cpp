#include "gameover/managers/rendermanager.h"
#include "gameover/graphics/framebuffer.h"
#include "gameover/engine.h"

#include "gameover/log.h"
#include "glad/glad.h"

namespace gameover::managers {
	void RenderManager::Inittialize(){

		GAMEOVER_INFO("OpengGL Info:\n Vendor:\t{}\n Render:\t{}\n Version:\t{}",
			(const char*)glGetString(GL_VENDOR),
			(const char*)glGetString(GL_RENDERER),
			(const char*)glGetString(GL_VERSION));

		// Enable OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		SetClearColor(
			static_cast<float>(0x64) / static_cast<float>(0xFF),
			static_cast<float>(0x95) / static_cast<float>(0xFF),
			static_cast<float>(0xED) / static_cast<float>(0xFF),
			1.0f
		);


	}
	void RenderManager::Shutdown() {
		while (mRenderCommands.size() > 0) {
			mRenderCommands.pop();
		}
	}

	void RenderManager::SetViewport(int x, int y, int w, int h)
	{
		glViewport(x, y, w, h);
	}

	void RenderManager::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void RenderManager::Clear()
	{
		GAMEOVER_ASSERT(mRenderCommands.size() == 0, "Unflushed render commands in queue!");
		while (mRenderCommands.size() > 0) {
			mRenderCommands.pop();
		}
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::Rendercommand> rc) {
		mRenderCommands.push(std::move(rc));
	}

	void RenderManager::Flush() {
		while (mRenderCommands.size() > 0) {
			auto rc = std::move(mRenderCommands.front());
			mRenderCommands.pop();

			rc->Excute();
		}
	}

	void RenderManager::SetWireframeMode(bool enable) {
		if (enable) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
	void RenderManager::PushFramebuffer(std::shared_ptr<graphics::Framebuffer> framebuffer) {
		mFramebuffers.push(framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetFbo());

		uint32_t w, h;
		framebuffer->GetSize(w, h);
		SetViewport(0, 0, w, h);

		float r, g, b, a;
		framebuffer->GetClearColour(r, g, b, a);
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	void RenderManager::PopFramebuffer() {
		GAMEOVER_ASSERT(mFramebuffers.size() > 0, "RenderManager::PopFramebuffer - empty stack");
		if (mFramebuffers.size() > 0) {
			mFramebuffers.pop();
			if (mFramebuffers.size() > 0) {
				auto nextfb = mFramebuffers.top();
				glBindFramebuffer(GL_FRAMEBUFFER, nextfb->GetFbo());
				uint32_t w, h;
				nextfb->GetSize(w, h);
				SetViewport(0, 0, w, h);
			}
			else {
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				auto& window = Engine::Instance().GetWindow();
				int w, h;
				window->GetSize(w, h);
				SetViewport(0, 0, w, h);
			}
		}
	}



}