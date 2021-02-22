#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021
// ====================================
#ifndef INTEGRIAN_INPUTMANAGER_H
#define INTEGRIAN_INPUTMANAGER_H

#include <unordered_map>
#include <vector>
#include <iostream>
#include <array>

#include "Command.h"
#include "Timer.h"
#include "PossibleInputs.h"
// Reference: https://stackoverflow.com/questions/25963966/c-function-pointer-callback-without-inheritance

// Henri-Thibault Huyghe came up with the idea of a superclass game input enum class
// and subclassed inputs for mouse and keyboard
// Rhidian De Wit made the implementation regarding the enum classes being stored in a struct
// We will most likely still have a different implementation, but it was worth mentioning, before either of us
// get seen as having plagiarized eachother's code

namespace Integrian
{
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

	enum class State
	{
		OnHeld = 0,
		OnRelease = 1 // Press and Release are the same
	};

	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		virtual ~InputManager();

		void AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState);

		void HandleInput();

		void SetWindowSize(const uint32_t width, const uint32_t height);

		[[nodiscard]] bool IsKeyboardKeyPressed(const KeyboardInput gameInput) const;
		[[nodiscard]] bool IsMouseButtonPressed(const MouseButton gameInput) const;
		[[nodiscard]] bool IsControllerButtonPressed(const ControllerInput gameInput, const uint32_t index) const;
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

		std::unordered_map<GameInput, std::vector<CommandAndButton>, GameInputKey, GameInputComparer> m_pCommands{};
		using InputCommandPair = std::pair<GameInput, std::vector<CommandAndButton>>;

		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		uint32_t m_AmountOfControllers;
		inline static constexpr uint16_t m_MaxAmountOfControllers{ 4 };

		std::array<SDL_GameController*, m_MaxAmountOfControllers> m_pControllers;
	};
}

#endif // !INTEGRIAN_INPUTMANAGER_H