#include "IntegrianPCH.h" // precompiled header
#include "Mouse.h" // Header

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
	const std::string eventName{ event.GetEvent() };
	if (eventName == "EndOfFrame")
	{
		for (const MouseButton& input : m_KeysToBeRemoved)
			m_MouseCommands.erase(input);

		m_KeysToBeRemoved.clear();
		return true;
	}
	else if (eventName == "Change_Application")
	{
		for (const MouseButton& input : m_KeysToBeRemoved)
			m_MouseCommands.erase(input);

		m_KeysToBeRemoved.clear();
		return true;
	}
	else
		return false;
}

void Integrian::Mouse::AddCommand(const MouseButton mouseButton, const State keyState, const std::function<void()>& pCommand)
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
				commandAndButton.pCommand();
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

const std::unordered_map<Integrian::MouseButton, std::vector<Integrian::CommandAndButton>>& Integrian::Mouse::GetCommands() const
{
	return m_MouseCommands;
}

void Integrian::Mouse::RemoveCommand(const std::function<void()>& pCommand)
{
	for (const CommandPair& commandPair : m_MouseCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.pCommand.target_type().hash_code() == pCommand.target_type().hash_code())
				m_KeysToBeRemoved.push_back(commandPair.first);
}