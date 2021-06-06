#pragma once
#ifndef INTEGRIAN_KEYBOARDINPUT_H
#define INTEGRIAN_KEYBOARDINPUT_H

#include "GameInput.h" // GameInput
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector

namespace Integrian
{
	class Command;
	class Keyboard final
	{
	public:
		~Keyboard();

	private:
		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&& other) noexcept;
		Keyboard& operator=(const Keyboard&) = delete;
		friend class InputManager;

		void AddCommand(const KeyboardInput keyboardInput, const State keyState, const std::function<void()>& pCommand);
		void ExecuteCommands();

		void ResetInputs();

		[[nodiscard]] bool IsPressed(const KeyboardInput gameInput) const;
		bool WasPressed(const State previousState) const;
		State GetKeystate(const KeyboardInput keyboardInput, const State previousState) const;
		[[nodiscard]] const std::unordered_map<KeyboardInput, std::vector<CommandAndButton>>& GetCommands() const;
		[[nodiscard]] KeyboardInput GetWhichKeyIsPressed() const noexcept;
		
		void RemoveCommand(const std::function<void()>& pCommand);

#pragma region EnumCheck
		template<typename Enum, Enum ... Values>
		class EnumCheck
		{};

		template<typename Enum>
		class EnumCheck<Enum>
		{
		public:
			template<typename IntType>
			static bool constexpr isValue(IntType)
			{
				return false;
			}
		};

		template<typename Enum, Enum V, Enum ... Next>
		class EnumCheck<Enum, V, Next...> : public EnumCheck<Enum, Next...>
		{
			using Super = EnumCheck<Enum, Next...>;
		public:
			template<typename IntType>
			static bool constexpr isValue(IntType v)
			{
				return v == static_cast<IntType>(V) || Super::isValue(v);
			}
		};
		
		using KI = KeyboardInput;

		using AllPossibleKeyboardEnumCheck = 
			EnumCheck<KI, KI::A, KI::B, KI::C, KI::D, KI::E, KI::F, KI::G, KI::H, KI::I, KI::J, KI::K, KI::L, KI::M, KI::N, KI::O, KI::P, KI::Q,
			KI::R, KI::S, KI::T, KI::U, KI::V, KI::W, KI::X, KI::Y, KI::Z, KI::Keyboard_0, KI::Keyboard_1, KI::Keyboard_2, KI::Keyboard_3,
			KI::Keyboard_4, KI::Keyboard_5, KI::Keyboard_6, KI::Keyboard_7, KI::Keyboard_8, KI::Keyboard_9, KI::Keypad_0, KI::Keypad_1,
			KI::Keypad_2, KI::Keypad_3, KI::Keypad_4, KI::Keypad_5, KI::Keypad_6, KI::Keypad_7, KI::Keypad_8, KI::Keypad_9, KI::F1, KI::F2,
			KI::F3, KI::F4, KI::F5, KI::F6, KI::F7, KI::F8, KI::F9, KI::F10, KI::F11, KI::F12, KI::Space, KI::Escape, KI::Enter, KI::Backspace,
			KI::Tab, KI::Minus, KI::Equals, KI::Leftbracket, KI::Rightbracket, KI::Backslash, KI::Semicolon, KI::Apostrophe, KI::Comma,
			KI::Slash, KI::Capslock, KI::Printscreen, KI::Scrolllock, KI::Keypad_Enter, KI::ArrowUp, KI::ArrowDown, KI::ArrowRight, KI::ArrowLeft>;
#pragma endregion

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