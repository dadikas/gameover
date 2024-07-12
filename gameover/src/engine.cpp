#include <iostream>
#include "engine.h"
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
}