#include "Mouse.h"
#include "Command.h"

Integrian::Mouse::~Mouse()
{
	m_pMouseCommands.clear();
}

void Integrian::Mouse::AddCommand(const MouseButton mouseButton, const State keyState, Command* pCommand)
{
	m_pMouseCommands[mouseButton].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::Mouse::ExecuteCommands(const Uint32 mouseState, const State currentHandledKeyState)
{
	for (const CommandPair& inputCommandPair : m_pMouseCommands)
		for (const CommandAndButton& commandAndButton : inputCommandPair.second)
			if (commandAndButton.keyState == currentHandledKeyState)
				if (static_cast<std::underlying_type<MouseButton>::type>(inputCommandPair.first) & mouseState)
					commandAndButton.pCommand->Execute();
}

bool Integrian::Mouse::IsMouseButtonPressed(const MouseButton gameInput) const
{
	return static_cast<std::underlying_type<MouseButton>::type>(gameInput) & SDL_GetMouseState(NULL, NULL);
}
