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
#include "PossibleInputs.h"
#include "GameInput.h"
#include "Keyboard.h"
#include "GameController.h"
#include "Mouse.h"
// Reference: https://stackoverflow.com/questions/25963966/c-function-pointer-callback-without-inheritance

// Henri-Thibault Huyghe came up with the idea of a superclass game input enum class
// and subclassed inputs for mouse and keyboard
// Rhidian De Wit made the implementation regarding the enum classes being stored in a struct
// We will most likely still have a different implementation, but it was worth mentioning, before either of us
// get seen as having plagiarized eachother's code
// update, the implementation was very much changed, but we still came up with this concept together

namespace Integrian
{
	class Command;
	class GameController;
	class Keyboard;
	class Mouse;
	class InputManager final
	{
	public:
		InputManager(const char* pFile, const int line);
		virtual ~InputManager() = default;

		void HandleInput();

		void SetWindowSize(const uint32_t width, const uint32_t height);

		[[nodiscard]] bool IsKeyboardKeyPressed(const KeyboardInput gameInput) const;
		[[nodiscard]] bool IsMouseButtonPressed(const MouseButton gameInput) const;
		[[nodiscard]] bool IsControllerButtonPressed(const ControllerInput gameInput, const uint8_t playerIndex = 0) const;
		[[nodiscard]] const Point2f& GetMousePosition() const;
		[[nodiscard]] double GetJoystickMovement(const SDL_GameControllerAxis axis, const uint8_t playerIndex = 0) const;
		[[nodiscard]] double GetTriggerMovement(const SDL_GameControllerAxis axis, const uint8_t playerIndex = 0) const;

	private:
		friend class CommandManager;

		void AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void RemoveInput(const GameInput& input, const uint8_t controllerIndex = 0);
		void RemoveCommandFromInput(const GameInput& input, Command* pCommand, const uint8_t controllerIndex = 0);
		void RemoveCommand(Command* pCommand, const uint8_t controllerIndex = 0);

		inline static bool m_IsInstantiated{};
		Point2f m_MousePosition;
		uint32_t m_WindowWidth;
		uint32_t m_WindowHeight;
		uint8_t m_AmountOfControllers;
		inline static constexpr uint8_t m_MaxAmountOfControllers{ 4 };

		std::array<GameController, m_MaxAmountOfControllers> m_Controllers;
		Keyboard m_Keyboard;
		Mouse m_Mouse;
	};
}

#endif // !INTEGRIAN_INPUTMANAGER_H