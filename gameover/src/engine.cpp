#include "engine.h"
#include "sdl2/SDL.h"
#include "log.h"
//#include <SDL2/SDL.h>
#include "core/opengl_window.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

namespace gameover
{
	Engine &Engine::Instance()
	{
		if (!mInstance)
		{
			mInstance = new Engine();
		}
		return *mInstance;
	}

	void Engine::Run()
	{
		if (Initialize())
		{
			float vertices[]{
				-0.5f,	-0.5f,	0.f,
				 0.f,	 0.5f,	0.f,
				 0.5f,	-0.5f,	0.f,
			};
			std::shared_ptr<graphics::Mesh> mesh = std::make_shared<graphics::Mesh>(&vertices[0], 3, 3);

			const char* vertextShader = R"(
				#version 410 core
				layout (location = 0) in vec3 position;				
				void main(){
					gl_Position = vec4(position, 1.0);
				}
			)";

			const char* fragmentShader = R"(
				#version 410 core
				out vec4 outColor;				
				void main(){
					outColor = vec4(1.0);
				}
			)";
			std::shared_ptr<graphics::Shader> shader = std::make_shared<graphics::Shader>(vertextShader, fragmentShader);

			while (mIsRunning)
			{
				mWindow->PumpEvents();

				mWindow->BeginRender();

				auto rc = std::make_unique<graphics::rendercommands::RenderMesh>(mesh, shader);
				mRendermanager.Submit(std::move(rc));
				mRendermanager.Flush();

				mWindow->EndRender();
			}
			Shutdown();
		}
	}

	// private
	bool Engine::Initialize()
	{
		bool ret = false;
		mWindow = new core::OpenGlWindow();

		GAMEOVER_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize() more than once");		
		if (!mIsInitialized)
		{
			
			mLogManager.Initialize();
			GetInfo();
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				GAMEOVER_ERROR("Error initializing SDL2: {}", SDL_GetError());
				ret = false;
			}
			else
			{
				SDL_version version;
				SDL_VERSION(&version);
				GAMEOVER_INFO("SDL2 {}.{}.{}", (int)version.major, (int)version.minor, (int)version.patch);
				if (mWindow->Create())
				{
					mRendermanager.Inittialize();

					ret = true;
					mIsRunning = true;
					mIsInitialized = true;
				}
			}
			if (!ret)
			{
				GAMEOVER_ERROR("Error initializing engine. Shutting down");
				Shutdown();
			}
			
		}
		return ret;
	}
	void Engine::Shutdown()
	{
		mIsRunning = false;
		// //Managers - usually in reverse order
		mRendermanager.Shutdown();
		mLogManager.Shutdown();

		mWindow->Shutdown();
		SDL_Quit();
	}

	void Engine::GetInfo()
	{

		GAMEOVER_TRACE("Gameover Engine v{}.{}", 0, 1);
#ifdef GAMEOVER_CONFIG_DEBUG
		GAMEOVER_DEBUG("Configuration: DEBUG");
#endif
#ifdef GAMEOVER_CONFIG_RELEASE
		GAMEOVER_DEBUG("Configuration: RELEASE");
#endif
#ifdef GAMEOVER_PLATFORM_WINDOWS
		GAMEOVER_WARN("Platform: WINDOWS");
#endif
#ifdef GAMEOVER_PLATFORM_LINUX
		GAMEOVER_WARN("Platform: LINUX");
#endif
	}

	Engine *Engine::mInstance = nullptr;
	Engine::Engine() : mIsRunning(false),
					   mIsInitialized(false) {}
}