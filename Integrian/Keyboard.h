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
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other);
		Keyboard& operator=(const Keyboard&) = delete;
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const;
		void RemoveInput(const KeyboardInput mouseButton);
		void RemoveCommandFromInput(const KeyboardInput mouseButton, Command* pCommand);

		std::unordered_map<KeyboardInput, std::vector<CommandAndButton>> m_KeyboardCommands{};

		using CommandPair = std::pair<KeyboardInput, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>::iterator;

		inline Keyboard& operator=(Integrian::Keyboard&& other) noexcept
		{
			m_KeyboardCommands = other.m_KeyboardCommands;
			other.m_KeyboardCommands.clear();

			return *this;
		}
	};
}

#endif // !INTEGRIAN_KEYBOARDINPUT_H