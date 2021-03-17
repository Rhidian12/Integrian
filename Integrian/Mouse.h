#pragma once
#ifndef INTEGRIAN_MOUSE_H
#define INTEGRIAN_MOUSE_H

#include "GameInput.h"
#include "PossibleInputs.h"
#include <unordered_map>

namespace Integrian
{
	class Mouse
	{
	public:
		~Mouse();

		void AddCommand(const MouseButton mouseButton, const State keyState, Command* pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const MouseButton gameInput) const;

	private:
		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&& other);
		Mouse& operator=(const Mouse&) = delete;
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const MouseButton mouseButton, const State previousState) const;
		void RemoveInput(const MouseButton mouseButton);
		void RemoveCommandFromInput(const MouseButton mouseButton, Command* pCommand);

		std::unordered_map<MouseButton, std::vector<CommandAndButton>> m_MouseCommands{};

		using CommandPair = std::pair<MouseButton, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<MouseButton, std::vector<CommandAndButton>>::iterator;
	
		inline Mouse& operator=(Mouse&& other) noexcept
		{
			m_MouseCommands = other.m_MouseCommands;
			other.m_MouseCommands.clear();

			return *this;
		}
	};
}

#endif // !INTEGRIAN_MOUSE_H