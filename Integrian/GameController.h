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

		void AddCommand(const ControllerInput controllerInput, const State keyState, Command* pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const ControllerInput controllerInput) const;

	private:
		GameController() = default;
		GameController(const uint8_t index);

		GameController(const GameController&) = delete;
		GameController(GameController&& other);
		GameController& operator=(const GameController&) = delete;
		friend class InputManager;

		bool WasPressed(const State previousState) const;
		State GetKeystate(const ControllerInput controllerInput, const State previousState) const;

		std::unordered_map<ControllerInput, std::vector<CommandAndButton>> m_pCommands;
		SDL_GameController* m_pSDLGameController;
		uint8_t m_Index;

		using CommandPair = std::pair<ControllerInput, std::vector<CommandAndButton>>;

		inline GameController& operator=(GameController&& other) noexcept
		{
			m_pCommands = other.m_pCommands;
			m_pSDLGameController = other.m_pSDLGameController;
			m_Index = other.m_Index;

			other.m_pCommands.clear();
			other.m_pSDLGameController = nullptr;

			return *this;
		}
	};
}

#endif // INTEGRIAN_GAMECONTROLLER_H