#pragma once
#include "gameover/graphics/rendercommands.h"

#include <memory>
#include <queue>
#include <stack>

#include "external/glm/glm.hpp"

#define GAMEOVER_SUBMIT_RC(type, ...) std::move(std::make_unique<gameover::graphics::rendercommands::type>(__VA_ARGS__))

namespace gameover::managers {
	class RenderManager {
		friend class graphics::rendercommands::PushFramebuffer;
		friend class graphics::rendercommands::PopFramebuffer;
	public:
		RenderManager(){}
		~RenderManager(){}

		void Inittialize();
		void Shutdown();

		void SetViewport(const glm::ivec4 dimensions);
		void SetClearColor(const glm::vec4 clearColour);
		void SetWireframeMode(bool enable);
		void Clear();
		void Submit(std::unique_ptr<graphics::rendercommands::Rendercommand> rc);
		void Flush();

	private:
		void PushFramebuffer(std::shared_ptr<graphics::Framebuffer> framebuffer);
		void PopFramebuffer();

	private:
		std::queue<std::unique_ptr<graphics::rendercommands::Rendercommand>> mRenderCommands;
		std::stack<std::shared_ptr<graphics::Framebuffer>> mFramebuffers;
	};
}