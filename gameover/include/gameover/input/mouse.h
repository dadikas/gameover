#pragma once

#include <array>

namespace gameover::input {
	class Mouse {
	public:
		static void Update();
		static void Initialize();

		inline static int X() { return x; };
		inline static int Y() { return y; };

		inline static int DX() { return x - xlast; }
		inline static int DY() { return y - ylast; }

		static bool Button(int button);
		static bool ButtonDown(int button);
		static bool ButtonUp(int button);
	private:
		constexpr static const int ButtonCount = 5;

		static int x, xlast;
		static int y, ylast;

		static std::array<bool, ButtonCount> buttons;
		static std::array<bool, ButtonCount> buttonslast;

	};
}

enum {
	GAMEOVER_INPUT_MOUSE_FIRST = 1,

	GAMEOVER_INPUT_MOUSE_LEFT = GAMEOVER_INPUT_MOUSE_FIRST,
	GAMEOVER_INPUT_MOUSE_MIDDLE = 2,
	GAMEOVER_INPUT_MOUSE_RIGHT = 3,
	GAMEOVER_INPUT_MOUSE_X1 = 4,
	GAMEOVER_INPUT_MOUSE_X2 =	5,	
	GAMEOVER_INPUT_MOUSE_LAST = 5,
};