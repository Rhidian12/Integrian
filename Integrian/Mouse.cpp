#include "Mouse.h"
#include "Command.h"
#include <algorithm>
#include <iostream>
#include "Logger.h"

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

void Integrian::Mouse::RemoveInput(const MouseButton mouseButton, const char* pFile, const int line)
{
#ifdef _DEBUG
	UMapIterator it{ m_MouseCommands.find(mouseButton) };
	if(it != m_MouseCommands.end())
		m_MouseCommands.erase(it);
	else
		Logger::LogSevereError(std::string{ "Tried to remove a non-existing input in file: " } + pFile + " and at line: " + std::to_string(line) + "\n");
#else
	try
	{
		m_MouseCommands.erase(mouseButton);
	}
	catch (const std::exception&)
	{
		Logger::LogSevereError(std::string{ "Tried to remove a non-existing input in file: " } + pFile + " and at line: " + std::to_string(line) + "\n");
	}
#endif
}

void Integrian::Mouse::RemoveCommandFromInput(const MouseButton mouseButton, Command* pCommand, const char* pFile, const int line)
{
	std::vector<CommandAndButton>& commands{ m_MouseCommands.find(mouseButton)->second };

#ifdef _DEBUG
	std::vector<CommandAndButton>::iterator it{ std::remove_if(commands.begin(),commands.end(),[pCommand](const CommandAndButton& commandAndButton)->bool
		{
			return commandAndButton.pCommand == pCommand;
		}) };

	if (it != commands.end())
		commands.erase(it, commands.end());
	else
		Logger::LogSevereError(std::string{ "Tried to remove a non-existing command in file: " } + pFile + " and at line: " + std::to_string(line) + "\n");
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
		Logger::LogSevereError(std::string{ "Tried to remove a non-existing command in file: " } + pFile + " and at line: " + std::to_string(line) + "\n");
	}
#endif
}
