#include "IntegrianPCH.h" // precompiled header
#include "GameController.h" // header
#include "Logger.h" // Logger
#include "ThreadManager.h" // ThreadManager

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
			Logger::LogError("Error in controller: " + std::to_string(index) + "\n" + SDL_GetError());
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

void Integrian::GameController::AddCommand(const ControllerInput controllerInput, const State keyState, const std::function<void()>& pCommand)
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
				commandAndButton.pCommand();
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

bool Integrian::GameController::OnEvent(const Event& event)
{
	const std::string eventName{ event.GetEvent() };

	return false;
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

double Integrian::GameController::GetJoystickMovement(const ControllerInput axis) const
{
	if (axis != ControllerInput::JoystickLeftHorizontalAxis && axis != ControllerInput::JoystickLeftVerticalAxis)
	{
		if (axis != ControllerInput::JoystickRightHorizontalAxis && axis != ControllerInput::JoystickRightVerticalAxis)
		{
			Logger::LogWarning("GetJoystickMovement() was called with a wrong parameter!\n");
			return 0.0;
		}
	}

	return Integrian::Clamp(double(SDL_GameControllerGetAxis(m_pSDLGameController, static_cast<SDL_GameControllerAxis>(axis)) / m_MaxJoystickValue), -1.0, 1.0); // map to [-1, 1]
}

double Integrian::GameController::GetTriggerMovement(const ControllerInput axis) const
{
	if (axis != ControllerInput::LeftTrigger && axis != ControllerInput::RightTrigger)
	{
		Logger::LogWarning("GetTriggerMovement() was called with the wrong parameter!\n");
		return 0.0;
	}

	return Integrian::Clamp(double(SDL_GameControllerGetAxis(m_pSDLGameController, static_cast<SDL_GameControllerAxis>(axis)) / m_MaxJoystickValue), 0.0, 1.0); // map to [0,1]
}

const std::unordered_map<Integrian::ControllerInput, std::vector<Integrian::CommandAndButton>>& Integrian::GameController::GetCommands() const
{
	return m_pCommands;
}

void Integrian::GameController::RemoveCommand(const std::function<void()>& pCommand)
{
	for (const CommandPair& commandPair : m_pCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand.target_type().hash_code() == pCommand.target_type().hash_code())
				m_pCommands.erase(commandPair.first);
}

void Integrian::GameController::ResetInputs()
{
	for (std::pair<const ControllerInput, std::vector<CommandAndButton>>& commandPair : m_pCommands)
		for (CommandAndButton& commandAndButton : commandPair.second)
			commandAndButton.previousKeystate = State::NotPressed;
}
