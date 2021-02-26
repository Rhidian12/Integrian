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
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const KeyboardInput gameInput) const;

	private:
		Keyboard() = default;
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const;

		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_pKeyboardCommands{};

		using CommandPair = std::pair<KeyboardInput, std::vector<CommandAndButton>>;
	};
}

#endif // !INTEGRIAN_KEYBOARDINPUT_H