#include "gameover/engine.h"
#include "gameover/log.h"
#include "gameover/app.h"

#include "gameover/core/opengl_window.h"

#include "gameover/input/mouse.h"
#include "gameover/input/keyboard.h"


#include "sdl2/SDL.h"

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

	void Engine::Run(App* app)
	{
		mLogManager.Initialize();
		GAMEOVER_ASSERT(!mApp, "Attemping to call Engine::Run when a valid app already exists");
		if (mApp) {
			return;
		}
		mApp = app;
		if (Initialize())
		{

			while (mIsRunning)
			{
				Update();
				Render();
			}
			Shutdown();
		}
	}

	// private
	bool Engine::Initialize()
	{
		bool ret = false;
		//mWindow = new core::OpenGlWindow();
		mWindow = std::make_shared<core::OpenGlWindow>();


		GAMEOVER_ASSERT(!mIsInitialized, "Attempting to call Engine::Initialize() more than once");		
		if (!mIsInitialized)
		{
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

				if (mWindow && mWindow->Create())
				{
					//initialize Managers
					mRendermanager.Inittialize();

					ret = true;
					mIsRunning = true;
					mIsInitialized = true;

					//initialize input
					input::Mouse::Initialize();
					input::Keyboard::Initialize();

					mApp->Initialize();
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
		mIsInitialized = false;

		mApp->Shutdown();
		// //Managers - usually in reverse order
		mRendermanager.Shutdown();
		

		mWindow->Shutdown();
		SDL_Quit();

		mLogManager.Shutdown();
	}

	void Engine::Update()
	{
		mWindow->PumpEvents();
		mApp->Update();
	}

	void Engine::Render()
	{
		mWindow->BeginRender();
		mApp->Render();
		mWindow->EndRender();
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

	Engine* Engine::mInstance = nullptr;

	Engine::Engine() : 
		mIsRunning(false),
		mIsInitialized(false),
		mApp(nullptr)
	{
			
	}
}