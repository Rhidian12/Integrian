#pragma once
#ifndef INTEGRIAN_GAMECONTROLLER_H
#define INTEGRIAN_GAMECONTROLLER_H

#include <unordered_map>
#include <vector>
#include "PossibleInputs.h"
#include "GameInput.h"

namespace Integrian
{
	class Command;
	class GameController final
	{
	public:
		~GameController();

		GameController(const GameController&) = delete;
		GameController(GameController&&) = delete;
		GameController& operator=(const GameController&) = delete;
		GameController& operator=(GameController&&) = delete;

		void AddCommand(const ControllerInput controllerInput, const State keyState, Command* pCommand);
		void ExecuteCommands(const State currentHandledKeyState);
		void ExecuteTriggers();
		[[nodiscard]] bool IsControllerButtonPressed(const ControllerInput gameInput) const;

	private:
		GameController(const uint8_t index);
		friend class InputManager;

		bool IsPressed(SDL_GameController* pController, const SDL_GameControllerAxis axis) const;
		bool WasPressed(const State previousState) const;
		State GetTriggerState(const SDL_GameControllerAxis axis, const State previousState, SDL_GameController* pController) const;

		std::unordered_map<ControllerInput, std::vector<CommandAndButton>> m_pCommands;
		SDL_GameController* m_pSDLGameController;
		std::vector<CommandAndButton> m_pLeftTriggerCommands{};
		std::vector<CommandAndButton> m_pRightTriggerCommands{};
		std::vector<State> m_pLeftTriggerPreviousStates{};
		std::vector<State> m_pRightTriggerPreviousStates{};
		uint8_t m_Index;

		using CommandPair = std::pair<ControllerInput, std::vector<CommandAndButton>>;
	};
}

#endif // INTEGRIAN_GAMECONTROLLER_H