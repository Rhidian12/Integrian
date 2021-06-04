#pragma once
#ifndef INTEGRIAN_GAMECONTROLLER_H
#define INTEGRIAN_GAMECONTROLLER_H

#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include "GameInput.h" // GameInput
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class Command;
	class GameController final : public IListener
	{
	public:
		~GameController();

		/*
		Public function to handle events. This is not supposed to be called manually
		*/
		virtual bool OnEvent(const Event& event) override;

	private:
		GameController() = default;
		GameController(const uint8_t index);

		GameController(const GameController&) = delete;
		GameController(GameController&& other) noexcept;
		GameController& operator=(const GameController&) = delete;
		friend class InputManager;

		void AddCommand(const ControllerInput controllerInput, const State keyState, const std::function<void()>& pCommand);
		void ExecuteCommands();

		[[nodiscard]] bool IsPressed(const ControllerInput controllerInput) const;
		[[nodiscard]] bool WasPressed(const State previousState) const;
		[[nodiscard]] State GetKeystate(const ControllerInput controllerInput, const State previousState) const;
		[[nodiscard]] double GetJoystickMovement(const ControllerInput axis) const;
		[[nodiscard]] double GetTriggerMovement(const ControllerInput axis) const;
		[[nodiscard]] const std::unordered_map<ControllerInput, std::vector<CommandAndButton>>& GetCommands() const;

		void RemoveCommand(const std::function<void()>& pCommand);

		void ResetInputs();

		std::unordered_map<ControllerInput, std::vector<CommandAndButton>> m_pCommands{};

		SDL_GameController* m_pSDLGameController{};
		uint8_t m_Index{};
		static constexpr double m_MaxJoystickValue{ 32767.0 }; // double instead of integer to prevent typecasting

		using CommandPair = std::pair<ControllerInput, std::vector<CommandAndButton>>;
		using UMapIterator = std::unordered_map<ControllerInput, std::vector<CommandAndButton>>::iterator;

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