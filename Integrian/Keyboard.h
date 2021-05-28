#pragma once
#ifndef INTEGRIAN_KEYBOARDINPUT_H
#define INTEGRIAN_KEYBOARDINPUT_H

#include "GameInput.h" // GameInput
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class Command;
	class Keyboard final : public IListener
	{
	public:
		~Keyboard();

		/*
		Public function to handle events. This is not supposed to be called manually
		*/
		virtual bool OnEvent(const Event& event) override;

	private:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) noexcept;
		Keyboard& operator=(const Keyboard&) = delete;
		friend class InputManager;

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, const std::function<void()>& pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const KeyboardInput gameInput) const;
		bool WasPressed(const State previousState) const;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const;
		[[nodiscard]] const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& GetCommands() const;
		
		void RemoveCommand(const std::function<void()>& pCommand);

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