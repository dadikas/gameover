#pragma once

#ifdef GO_PLATFROM_WINDOWS

extern gameover::App* CreateApp();
int main(int argc, int char** argv) {
	auto app = gameover::CreateApp();
	delete app;
	return 0;
}

#endif 


#include "gameover/engine.h"
#include "gameover/app.h"

extern gameover::App* CreateApp();
int main() {
	gameover::App* app = CreateApp();
	gameover::Engine::Instance().Run(app);
	delete app;
	return 0;
}

