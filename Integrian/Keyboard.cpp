#include "pch.h"
#include "Keyboard.h"
#include "Command.h"

Integrian::Keyboard::~Keyboard()
{
	m_pKeyboardCommands.clear();
}

void Integrian::Keyboard::AddCommand(const KeyboardInput keyboardInput, const State keyState, Command* pCommand)
{
	m_pKeyboardCommands[keyboardInput].push_back(CommandAndButton{ pCommand,keyState });
}

void Integrian::Keyboard::ExecuteCommands(const State currentHandledKeyState, const SDL_Scancode currentKey)
{
	for(const CommandPair& commandPair : m_pKeyboardCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.keyState == currentHandledKeyState)
				if (static_cast<SDL_Scancode>(commandPair.first) == currentKey)
					commandAndButton.pCommand->Execute();
}

void Integrian::Keyboard::ExecuteCommands(const Uint8* const pStates, const State currentHandledKeyState)
{
	for (const CommandPair& commandPair : m_pKeyboardCommands)
		for (const CommandAndButton& commandAndButton : commandPair.second)
			if (commandAndButton.keyState == currentHandledKeyState)
				if (pStates[static_cast<SDL_Scancode>(commandPair.first)])
					commandAndButton.pCommand->Execute();
}

bool Integrian::Keyboard::IsKeyboardKeyPressed(const KeyboardInput gameInput) const
{
	return SDL_GetKeyboardState(nullptr)[static_cast<SDL_Scancode>(gameInput)];
}
