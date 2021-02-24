#pragma once
#ifndef INTEGRIAN_GAMEINPUT_H
#define INTEGRIAN_GAMEINPUT_H

#include "PossibleInputs.h"

namespace Integrian
{
	class Command;

	enum class State
	{
		OnHeld = 1,
		OnRelease = 2,
		OnPress = 3, // Only use this for controllers!


		NotPressed = 0 // internal usage
	};

	struct CommandAndButton final
	{
		CommandAndButton(Command* pCommand, const State keyState)
			: pCommand{ pCommand }
			, keyState{ keyState }
		{
		}

		Command* pCommand;
		State keyState;
	};

	struct GameInput final
	{
		explicit GameInput(const ControllerInput controllerInput)
			: controllerInput{ controllerInput }
		{
		}
		explicit GameInput(const KeyboardInput keyboardInput)
			: keyboardInput{ keyboardInput }
		{
		}
		explicit GameInput(const MouseButton mouseButton)
			: mouseButton{ mouseButton }
		{
		}

		ControllerInput controllerInput{ ControllerInput::INVALID };
		KeyboardInput keyboardInput{ KeyboardInput::INVALID };
		MouseButton mouseButton{ MouseButton::INVALID };

		uint64_t id{ GetRandomNumber(uint64_t(0), std::numeric_limits<uint64_t>::max()) };
	};
}

#endif // !INTEGRIAN_GAMEINPUT_H