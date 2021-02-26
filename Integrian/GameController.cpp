#include "GameController.h"
#include "Command.h"

Integrian::GameController::GameController(const uint8_t index)
	: m_pCommands{}
	, m_pSDLGameController{}
	, m_Index{ index }
{
	if (SDL_IsGameController(index))
	{
		m_pSDLGameController = SDL_GameControllerOpen(index);

		if (!m_pSDLGameController)
		{
			Logger::GetInstance().Log("Error in controller: ", ErrorLevel::error);
			Logger::GetInstance().Log(std::to_string(index), ErrorLevel::error);
			Logger::GetInstance().Log(SDL_GetError(), ErrorLevel::error);
		}
	}
}

Integrian::GameController::GameController(GameController&& other)
{
	m_pCommands = other.m_pCommands;
	m_pSDLGameController = other.m_pSDLGameController;
	m_Index = other.m_Index;

	other.m_pCommands.clear();
	other.m_pSDLGameController = nullptr;
}

Integrian::GameController::~GameController()
{
	// Below code SHOULD work, but does not work. Throws read access violations, even though this is the exact
	// way SDL defines this
// TODO: figure out why this is happening
//	if (m_pSDLGameController)
//	{
//		SDL_GameControllerClose(m_pSDLGameController);
//		m_pSDLGameController = nullptr;
//	}

	m_pCommands.clear();
}

void Integrian::GameController::AddCommand(const ControllerInput controllerInput, const State keyState, Command* pCommand)
{
	m_pCommands[controllerInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::GameController::ExecuteCommands()
{
	for (std::pair<const ControllerInput, std::vector<CommandAndButton>>& commandPair : m_pCommands)
	{
		for (CommandAndButton& commandAndButton : commandPair.second)
		{
			const State currentKeystate{ GetKeystate(commandPair.first, commandAndButton.previousKeystate) };
			if (currentKeystate == commandAndButton.wantedKeystate)
			{
				commandAndButton.pCommand->Execute();
			}
			commandAndButton.previousKeystate = currentKeystate;
		}
	}
}

bool Integrian::GameController::IsPressed(const ControllerInput controllerInput) const
{
	if (controllerInput == ControllerInput::LeftTrigger)
		return (SDL_GameControllerGetAxis(m_pSDLGameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0);

	if (controllerInput == ControllerInput::RightTrigger)
		return (SDL_GameControllerGetAxis(m_pSDLGameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0);

	else
		return (SDL_GameControllerGetButton(m_pSDLGameController, static_cast<SDL_GameControllerButton>(controllerInput)) > 0);
}

bool Integrian::GameController::WasPressed(const State previousState) const
{
	return (previousState == State::OnPress || previousState == State::OnHeld);
}

Integrian::State Integrian::GameController::GetKeystate(const ControllerInput controllerInput, const State previousState) const
{
	if (WasPressed(previousState))
	{
		if (IsPressed(controllerInput))
			return State::OnHeld;

		else
			return State::OnRelease;
	}

	if (IsPressed(controllerInput))
		return State::OnPress;

	return State::NotPressed;
}
