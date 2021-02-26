#include "Mouse.h"
#include "Command.h"

Integrian::Mouse::Mouse(Mouse&& other)
{
	m_MouseCommands = other.m_MouseCommands;
	other.m_MouseCommands.clear();
}

Integrian::Mouse::~Mouse()
{
	m_MouseCommands.clear();
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
