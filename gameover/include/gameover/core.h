
#pragma once

#ifdef GO_PLATFORM_WINDOWS
	#ifdef GO_BUILD_DLL
		#define GAMEOVER_API __declspec(dllexport)
	#else
		#define GAMEOVER_API __declspec(dllimport)
	#endif
#elif defined(__unix__)
	#ifdef GO_BUILD_DLL
		#define GAMEOVER_API __attribute__((visibility("default")))
	#else
		#define GAMEOVER_API
	#endif
#else
	#error Unsupported platform!
#endif
