#include "gameover/input/joystick.h"
#include "gameover/log.h"

#include <algorithm>

#include "sdl2/SDL_events.h"
#include "sdl2/SDL_gamecontroller.h"

namespace gameover::input {
	std::unordered_map<int, std::unique_ptr<gameover::input::Joystick::Controller>> Joystick::availableJoysticks;

	void Joystick::OnJoystickConnected(SDL_ControllerDeviceEvent& e)
	{
		int deviceIndex = e.which;

		if (SDL_IsGameController(deviceIndex)) {
			auto c = std::make_unique<Controller>();
			c->gc = SDL_GameControllerOpen(deviceIndex);
			if (c->gc) {
				c->joystickIndex = deviceIndex;

				std::fill(c->buttons.begin(), c->buttons.end(), false);
				std::fill(c->lastButtons.begin(), c->lastButtons.end(), false);
				std::fill(c->axes.begin(), c->axes.end(), 0.f);
				std::fill(c->lastAxes.begin(), c->lastAxes.end(), 0.f);

				int mapIndex = GetNextFreeIndex();
				GAMEOVER_TRACE("Joystick connected: mapIndex({}), deviceIndex({})", mapIndex, deviceIndex);
				availableJoysticks[mapIndex] = std::move(c);
			}
			else {
				GAMEOVER_ERROR("Error opening gam controller with Device Index {}: {}", deviceIndex);
			}
		}

	}

	void Joystick::OnJoystickDisconnected(SDL_ControllerDeviceEvent& e)
	{
		int deviceIndex = e.which;
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); ++it) {
			Controller* c = it->second.get();
			if (c->joystickIndex == deviceIndex) {
				GAMEOVER_TRACE("Joystick disconnected: {}", deviceIndex);
				SDL_GameControllerClose(c->gc);
				availableJoysticks.erase(it);
				break;
			}

		}

	}

	void Joystick::Shutdown()
	{
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); ++it) {
			Controller* c = it->second.get();
			SDL_GameControllerClose(c->gc);
			it = availableJoysticks.erase(it);
		}
	}

	void Joystick::Update()
	{
		for (auto it = availableJoysticks.begin(); it != availableJoysticks.end(); ++it) {
			Controller* c = it->second.get();
			GAMEOVER_ASSERT(c && c->gc, "Invalid game controller in availableJoysticks map");
			if (c && c->gc) {
				c->lastButtons = c->buttons;
				c->lastAxes = c->axes;

				for (unsigned int i = 0; i < static_cast<int>(Button::Count); ++i) {
					c->buttons[i] = SDL_GameControllerGetButton(c->gc, static_cast<SDL_GameControllerButton>(i));
				}
				for (unsigned int i = 0; i < static_cast<int>(Axis::Count); ++i) {
					c->axes[i] = SDL_GameControllerGetAxis(c->gc, static_cast<SDL_GameControllerAxis>(i));
				}

			}

		}
	}

	bool Joystick::IsJoystickAvailable(int joystickId)
	{
		return availableJoysticks.count(joystickId) > 0;
	}

	bool Joystick::GetButton(int joystickId, Button button)
	{
		auto it = availableJoysticks.find(joystickId);
		if (it != availableJoysticks.end()) {
			return it->second->buttons[static_cast<int>(button)];
		}
		GAMEOVER_ERROR("Joystick with id {} is not available!", joystickId);
		return false;
	}

	bool Joystick::GetButtonDown(int joystickId, Button button)
	{
		auto it = availableJoysticks.find(joystickId);
		if (it != availableJoysticks.end()) {
			return it->second->buttons[static_cast<int>(button)] && !it->second->buttons[static_cast<int>(button)];
		}
		GAMEOVER_ERROR("Joystick with id {} is not available!", joystickId);
		return false;
	}

	bool Joystick::GetButtonUp(int joystickId, Button button)
	{
		auto it = availableJoysticks.find(joystickId);
		if (it != availableJoysticks.end()) {
			return it->second->buttons[static_cast<int>(button)] && !it->second->buttons[static_cast<int>(button)];
		}
		GAMEOVER_ERROR("Joystick with id {} is not available!", joystickId);
		return false;
	}

	float Joystick::GetAxis(int joystickId, Axis axis)
	{
		auto it = availableJoysticks.find(joystickId);
		if (it != availableJoysticks.end()) {
			float val = it->second->axes[static_cast<int>(axis)];
			return abs(val) > deadzone? val:0.f;
		}
		GAMEOVER_ERROR("Joystick with id {} is not available!", joystickId);
		return 0.f;
	}

	int Joystick::GetNextFreeIndex()
	{
		int ret = -1;

		for (int i = 0; i < SDL_NumJoysticks(); ++i) {
			ret = i;
			break;
		}
		return ret;
	}

	float Joystick::deadzone;


}