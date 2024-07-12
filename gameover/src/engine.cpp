#include <iostream>
#include "engine.h"
#include "sdl2/SDL.h"

namespace gameover{

    void getInfo(){
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

	bool init(){
		bool ret = true;
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			ret = false;
		}
		else{
			SDL_version version;
			SDL_VERSION(&version);
			std::cout << "SDL Version: " << (int)version.major << "." << (int)version.minor << "." << (int)version.patch << std::endl;
		}
		return ret;
	}
	void quit(){
		SDL_Quit();
	}
}