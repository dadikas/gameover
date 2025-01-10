#pragma once
#include "graphics/rendercommands.h"

#include <memory>
#include <queue>

namespace gameover::managers {
	class RenderManager {
	public:
		RenderManager(){}
		~RenderManager(){}

		void Inittialize();
		void Shutdown();

		void SetClearColor(float r, float g, float b, float a);

		void Clear();

		void Submit(std::unique_ptr<graphics::rendercommands::Rendercommand> rc);

		void Flush();

	private:
		std::queue<std::unique_ptr<graphics::rendercommands::Rendercommand>> mRenderCommands;
	};
}