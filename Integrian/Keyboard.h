#pragma once
#ifndef INTEGRIAN_KEYBOARDINPUT_H
#define INTEGRIAN_KEYBOARDINPUT_H

#include "GameInput.h"
#include "PossibleInputs.h"
#include <unordered_map>

namespace Integrian
{
	class Command;
	class Keyboard final
	{
	public:
		~Keyboard();

		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* pCommand);
		void ExecuteCommands(const State currentHandledKeyState, const SDL_Scancode currentKey);
		void ExecuteCommands(const Uint8* const pStates, const State currentHandledKeyState);
		[[nodiscard]] bool IsKeyboardKeyPressed(const KeyboardInput gameInput) const;

	private:
		Keyboard() = default;
		friend class InputManager;

		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_pKeyboardCommands{};

		using CommandPair = std::pair<KeyboardInput, std::vector<CommandAndButton>>;
	};
}

#endif // !INTEGRIAN_KEYBOARDINPUT_H