#include "Keyboard.h" // Header
#include "Command.h" // Command::Execute()
#include "Logger.h" // Logger
#include "ThreadManager.h" // ThreadManager

Integrian::Keyboard::Keyboard(Keyboard&& other)
{
	m_KeyboardCommands = other.m_KeyboardCommands;
	other.m_KeyboardCommands.clear();
}


Integrian::Keyboard::~Keyboard()
{
	m_KeyboardCommands.clear();
}

bool Integrian::Keyboard::OnEvent(const Event& event)
{
	switch (event.GetEvent())
	{
	case Events::EndOfFrame:
	{
		ThreadManager::GetInstance().AssignThread([this]()
			{
				for (const KeyboardInput& input : m_KeysToBeRemoved)
					m_KeyboardCommands.erase(input);

				m_KeysToBeRemoved.clear();
			});
		return true;
	}
	break;
	default:
		return false;
		break;
	}
}

void Integrian::Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* pCommand)
{
	m_KeyboardCommands[keyboardInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::Keyboard::ExecuteCommands()
{
	for (std::pair<const KeyboardInput, std::vector<CommandAndButton>>& commandPair : m_KeyboardCommands)
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

bool Integrian::Keyboard::IsPressed(const KeyboardInput gameInput) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(gameInput)];
}

bool Integrian::Keyboard::WasPressed(const State previousState) const
{
	return (previousState == State::OnPress || previousState == State::OnHeld);
}

Integrian::State Integrian::Keyboard::GetKeystate(const KeyboardInput keyboardInput, const State previousState) const
{
	if (WasPressed(previousState))
	{
		if (IsPressed(keyboardInput))
			return State::OnHeld;

		else
			return State::OnRelease;
	}

	if (IsPressed(keyboardInput))
		return State::OnPress;

	return State::NotPressed;
}

void Integrian::Keyboard::RemoveCommand(Command* pCommand)
{
	for (const CommandPair& commandPair : m_KeyboardCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand == pCommand)
				m_KeysToBeRemoved.push_back(commandPair.first);
}