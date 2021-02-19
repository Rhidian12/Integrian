#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021
// ====================================
#ifndef INTEGRIAN_INPUTMANAGER_H
#define INTEGRIAN_INPUTMANAGER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <iostream>

#include "Command.h"
#include "Timer.h"
#include "PossibleInputs.h"
// Reference: https://stackoverflow.com/questions/25963966/c-function-pointer-callback-without-inheritance

// Henri-Thibault Huyghe came up with the idea of a superclass game input enum class
// and subclassed inputs for mouse and keyboard
// Rhidian De Wit made the implementation regarding the enum classes being stored in a union
// We will most likely still have a different implementation, but it was worth mentioning, before either of us
// get seen as having plagiarized eachother's code

namespace Integrian
{
	union GameInput
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

		ControllerInput controllerInput;
		KeyboardInput keyboardInput;
		MouseButton mouseButton;

		uint32_t id{ GetRandomNumber(uint32_t(0), std::numeric_limits<uint32_t>::max()) };
	};

	enum class State
	{
		OnHeld = 0,
		OnPress = 1 // Press and Release are the same
	};

	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		virtual ~InputManager();

		void AddCommand(const GameInput gameInput, Command* pCommand, const State keyState);

		void HandleInput();

		void SetWindowSize(const uint32_t width, const uint32_t height);

		[[nodiscard]] const Point2f& GetMousePosition() const;

	private:
		InputManager();
		friend class Singleton<InputManager>;

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

		struct GameInputKey final
		{
			size_t operator()(const GameInput input) const
			{
				return input.id;
			}
		};
		struct GameInputComparer final
		{
			bool operator()(const GameInput a, const GameInput b) const
			{
				return a.id == b.id;
			}
		};

		//std::unordered_map<Uint8, std::vector<Command*>>	m_KeyDownKeybindCommands;
		//std::unordered_map<Uint8, std::vector<Command*>>	m_KeyUpKeybindCommands;
		//std::unordered_map<MouseButton, std::vector<Command*>>	m_MouseDownMouseCommands;
		//std::unordered_map<MouseButton, std::vector<Command*>>	m_MouseUpMouseCommands;

		std::unordered_map<GameInput, std::vector<CommandAndButton>, GameInputKey, GameInputComparer> m_pCommands{};

		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;

		//using KeybindFunctionWrapperPair = std::pair<Uint8, std::vector<Command*>>;
		//using MouseFunctionWrapperPair = std::pair<MouseButton, std::vector<Command*>>;
		using InputCommandPair = std::pair<GameInput, std::vector<CommandAndButton>>;
	};
}

#endif // !INTEGRIAN_INPUTMANAGER_H