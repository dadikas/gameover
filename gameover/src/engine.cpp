#include <iostream>
#include "engine.h"
#include "sdl2/SDL.h"

namespace gameover{
	Engine& Engine::Instance(){
		if(!mInstance)
		{
			mInstance = new Engine();
		}
		return *mInstance;
	}
	
	void Engine::Run(){
		if(Initialize())
		{
			while(mIsRunning){
				mWindow.PumpEvents();
			}
			Shutdown();
		}
	}
	
	//private
	bool Engine::Initialize(){
		bool ret = false;
		if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "Error initializing SDL2 " << SDL_GetError() << std::endl;
			ret = false;
		}
		else
		{
			SDL_version version;
			SDL_VERSION(&version);
			std::cout << "SDL2 Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;
			if (mWindow.Create())
			{
				ret = true;
				mIsRunning = true;
			}
		}
		if(!ret){
			std::cout << "Error initializing engine. Shutting down" << std::endl;
			Shutdown();
		}
		return ret;
	}
	void Engine::Shutdown(){
		mWindow.Shutdown();
		SDL_Quit();
	}

    void Engine::GetInfo(){
#ifdef GAMEOVER_CONFIG_DEBUG
		std::cout << "Configuration: DEBUG" << std::endl;
#endif
#ifdef GAMEOVER_CONFIG_RELEASE
		std::cout << "Configuration: RELEASE" << std::endl;
#endif
#ifdef GAMEOVER_PLATFORM_WINDOWS
		std::cout << "Platform: WINDOWS" << std::endl;
#endif
#ifdef GAMEOVER_PLATFORM_LINUX
		std::cout << "Platform: LINUX" << std::endl;
#endif      
    }

	Engine* Engine::mInstance = nullptr;
	Engine::Engine()
		:mIsRunning(false)
	{
		GetInfo();
	}
}