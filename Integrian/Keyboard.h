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

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const KeyboardInput gameInput) const;

	private:
		Keyboard() = default;
		Keyboard(const Keyboard& other);
		Keyboard(Keyboard&& other);
		Keyboard& operator=(const Keyboard& other);
		Keyboard& operator=(Keyboard&& other);
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const;

		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_KeyboardCommands{};

		using CommandPair = std::pair<KeyboardInput, std::vector<CommandAndButton>>;

		inline Keyboard& operator=(const Integrian::Keyboard& other)
		{
			m_KeyboardCommands = other.m_KeyboardCommands;
		}
		inline Keyboard& operator=(Integrian::Keyboard&& other)
		{
			m_KeyboardCommands = other.m_KeyboardCommands;
			other.m_KeyboardCommands.clear();
		}
	};
}

#endif // !INTEGRIAN_KEYBOARDINPUT_H