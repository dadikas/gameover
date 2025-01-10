#include "managers/rendermanager.h"

#include "log.h"
#include "glad/glad.h"

namespace gameover::managers {
	void RenderManager::Inittialize(){

		GAMEOVER_INFO("OpengGL Info:\n Vendor:\t{}\n Render:\t{}\n Version:\t{}\n",
			(const char*)glGetString(GL_VENDOR),
			(const char*)glGetString(GL_RENDER),
			(const char*)glGetString(GL_VERSION));

		// Enable OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClearColor(
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

	void RenderManager::SetClearColor(float r, float g, float b, float a) {
		glClearColor(r, b, g, a);
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

}