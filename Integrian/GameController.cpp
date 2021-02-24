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
	m_pLeftTriggerCommands.clear();
	m_pRightTriggerCommands.clear();
	m_pLeftTriggerPreviousStates.clear();
	m_pRightTriggerPreviousStates.clear();
}

void Integrian::GameController::AddCommand(const ControllerInput controllerInput, const State keyState, Command* pCommand)
{
	if (controllerInput == ControllerInput::LeftTrigger)
	{
		m_pLeftTriggerCommands.push_back(CommandAndButton{ pCommand,keyState });
		m_pLeftTriggerPreviousStates.reserve(m_pLeftTriggerCommands.size());
		m_pLeftTriggerPreviousStates.push_back(State::NotPressed);
	}

	else if (controllerInput == ControllerInput::RightTrigger)
	{
		m_pRightTriggerCommands.push_back(CommandAndButton{ pCommand,keyState });
		m_pRightTriggerPreviousStates.reserve(m_pRightTriggerCommands.size());
		m_pRightTriggerPreviousStates.push_back(State::NotPressed);
	}

	else
		m_pCommands[controllerInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::GameController::ExecuteCommands(const State currentHandledKeyState)
{
	for (const CommandPair& commandPair : m_pCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.keyState == currentHandledKeyState)
				if (SDL_GameControllerGetButton(m_pSDLGameController, static_cast<SDL_GameControllerButton>(commandPair.first)) > 0)
					commandAndButton.pCommand->Execute();
}

void Integrian::GameController::ExecuteTriggers()
{
	for (size_t i{}; i < m_pLeftTriggerCommands.size(); ++i)
		if (GetTriggerState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT, m_pLeftTriggerPreviousStates[i], m_pSDLGameController) == m_pLeftTriggerCommands[i].keyState)
			m_pLeftTriggerCommands[i].pCommand->Execute();

	for (size_t i{}; i < m_pRightTriggerCommands.size(); ++i)
		if (GetTriggerState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT, m_pRightTriggerPreviousStates[i], m_pSDLGameController) == m_pRightTriggerCommands[i].keyState)
			m_pRightTriggerCommands[i].pCommand->Execute();

	for (size_t i{}; i < m_pLeftTriggerCommands.size(); ++i)
		m_pLeftTriggerPreviousStates[i] = GetTriggerState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT, m_pLeftTriggerPreviousStates[i], m_pSDLGameController);

	for (size_t i{}; i < m_pRightTriggerCommands.size(); ++i)
		m_pRightTriggerPreviousStates[i] = GetTriggerState(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT, m_pRightTriggerPreviousStates[i], m_pSDLGameController);
}

bool Integrian::GameController::IsPressed(SDL_GameController* pController, const SDL_GameControllerAxis axis) const
{
	return (SDL_GameControllerGetAxis(pController, axis) > 0);
}

bool Integrian::GameController::WasPressed(const State previousState) const
{
	return (previousState == State::OnPress || previousState == State::OnHeld);
}

Integrian::State Integrian::GameController::GetTriggerState(const SDL_GameControllerAxis axis, const State previousState, SDL_GameController* pController) const
{
	if (WasPressed(previousState))
	{
		if (IsPressed(pController, axis))
			return State::OnHeld;

		else
			return State::OnRelease;
	}

	if (IsPressed(pController, axis))
		return State::OnPress;

	return State::NotPressed;
}

bool Integrian::GameController::IsControllerButtonPressed(const ControllerInput gameInput) const
{
	if (ControllerInput::LeftTrigger == gameInput)
		return SDL_GameControllerGetAxis(m_pSDLGameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0;

	else if (ControllerInput::RightTrigger == gameInput)
		return SDL_GameControllerGetAxis(m_pSDLGameController, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0;

	else
		return SDL_GameControllerGetButton(m_pSDLGameController, static_cast<SDL_GameControllerButton>(gameInput));
}