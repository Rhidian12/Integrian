#include "GameController.h"
#include "Logger.h"
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
			Logger::GetInstance().Log(" ", ErrorLevel::error);
			Logger::GetInstance().Log(SDL_GetError(), ErrorLevel::error);
		}
	}
}

Integrian::GameController::GameController(GameController&& other) noexcept
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

double Integrian::GameController::GetJoystickMovement(const SDL_GameControllerAxis axis) const
{
	if (axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX && axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY)
	{
		if (axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX && axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY)
		{
			Logger::GetInstance().Log("GetJoystickMovement() was called with a wrong parameter!", ErrorLevel::warning);
			return 0.0;
		}
	}

	return Integrian::Clamp(double(SDL_GameControllerGetAxis(m_pSDLGameController, axis) / m_MaxJoystickValue), -1.0, 1.0); // map to [0,1]
}

double Integrian::GameController::GetTriggerMovement(const SDL_GameControllerAxis axis) const
{
	if (axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT && axis != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
	{
		Logger::GetInstance().Log("GetTriggerMovement() was called with the wrong parameter!", ErrorLevel::warning);
		return 0.0;
	}

	return Integrian::Clamp(double(SDL_GameControllerGetAxis(m_pSDLGameController, axis) / m_MaxJoystickValue), 0.0, 1.0); // map to [0,1]
}

void Integrian::GameController::RemoveInput(const ControllerInput controllerInput)
{
#ifdef _DEBUG
	UMapIterator it{ m_pCommands.find(controllerInput) };
	if (it != m_pCommands.end())
		m_pCommands.erase(it);
	else
	{
		// TODO: Come up with a better logging system, this is ridicilous
		Logger& logger{ Logger::GetInstance() };
		logger.Log("Tried to remove a non-existing input, ", ErrorLevel::severeError);
		logger.Log("In file and at line: ", ErrorLevel::severeError);
		logger.Log(__FILE__, ErrorLevel::severeError);
		logger.Log(std::to_string(__LINE__), ErrorLevel::severeError);
		logger.Log("\n", ErrorLevel::severeError);
	}
#else
	try
	{
		m_pCommands.erase(controllerInput);
	}
	catch (const std::exception&)
	{
		// TODO: Make this print to a file
		std::cerr << "Tried to remove a non-existent input" << std::endl;
	}
#endif
}

void Integrian::GameController::RemoveCommandFromInput(const ControllerInput controllerInput, Command* pCommand)
{
	std::vector<CommandAndButton>& commands{ m_pCommands.find(controllerInput)->second };

#ifdef _DEBUG
	std::vector<CommandAndButton>::iterator it{ std::remove_if(commands.begin(),commands.end(),[pCommand](const CommandAndButton& commandAndButton)->bool
		{
			return commandAndButton.pCommand == pCommand;
		}) };

	if (it != commands.end())
		commands.erase(it, commands.end());
	else
	{
		Logger& logger{ Logger::GetInstance() };
		logger.Log("Tried to remove a non-existing command, ", ErrorLevel::severeError);
		logger.Log("In file and at line: ", ErrorLevel::severeError);
		logger.Log(__FILE__, ErrorLevel::severeError);
		logger.Log(std::to_string(__LINE__), ErrorLevel::severeError);
		logger.Log("\n", ErrorLevel::severeError);
	}
#else
	try
	{
		commands.erase(std::remove_if(commands.begin(), commands.end(), [pCommand](const CommandAndButton& commandAndButton)->bool
			{
				return commandAndButton.pCommand == pCommand;
			}));
	}
	catch (const std::exception&)
	{
		// TODO: Make this print something to a log file
		std::cerr << "Tried to remove non-existing command" << std::endl;
	}
#endif
}

void Integrian::GameController::RemoveCommand(Command* pCommand)
{
	for (const CommandPair& commandPair : m_pCommands)
	{
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand == pCommand)
				m_pCommands.erase(commandPair.first);
	}
}
