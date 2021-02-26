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
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const ControllerInput controllerInput) const;

	private:
		GameController(const uint8_t index);
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const ControllerInput controllerInput, const State previousState) const;

		std::unordered_map<ControllerInput, std::vector<CommandAndButton>> m_pCommands;
		SDL_GameController* m_pSDLGameController;
		uint8_t m_Index;



		using CommandPair = std::pair<ControllerInput, std::vector<CommandAndButton>>;
	};
}

#endif // INTEGRIAN_GAMECONTROLLER_H