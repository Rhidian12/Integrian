#include "Mouse.h" // Header
#include "Command.h" // Command::Execute()
#include "Logger.h" // Logger
#include "ThreadManager.h" // ThreadManager

Integrian::Mouse::Mouse(Mouse&& other)
{
	m_MouseCommands = other.m_MouseCommands;
	other.m_MouseCommands.clear();
}

Integrian::Mouse::~Mouse()
{
	m_MouseCommands.clear();
}

bool Integrian::Mouse::OnEvent(const Event& event)
{
	switch (event.GetEvent())
	{
	case Events::EndOfFrame:
	{
		ThreadManager::GetInstance().AssignThread([this]()
			{
				for (const MouseButton& input : m_KeysToBeRemoved)
					m_MouseCommands.erase(input);

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

void Integrian::Mouse::AddCommand(const MouseButton mouseButton, const State keyState, Command* pCommand)
{
	m_MouseCommands[mouseButton].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::Mouse::ExecuteCommands()
{
	for (std::pair<const MouseButton, std::vector<CommandAndButton>>& commandPair : m_MouseCommands)
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

bool Integrian::Mouse::IsPressed(const MouseButton gameInput) const
{
	return static_cast<std::underlying_type<MouseButton>::type>(gameInput) == SDL_GetMouseState(NULL, NULL);
}

bool Integrian::Mouse::WasPressed(const State previousState) const
{
	return (previousState == State::OnPress || previousState == State::OnHeld);
}

Integrian::State Integrian::Mouse::GetKeystate(const MouseButton mouseButton, const State previousState) const
{
	if (WasPressed(previousState))
	{
		if (IsPressed(mouseButton))
			return State::OnHeld;

		else
			return State::OnRelease;
	}

	if (IsPressed(mouseButton))
		return State::OnPress;

	return State::NotPressed;
}

void Integrian::Mouse::RemoveCommand(Command* pCommand)
{
	for (const CommandPair& commandPair : m_MouseCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand == pCommand)
				m_KeysToBeRemoved.push_back(commandPair.first);
}