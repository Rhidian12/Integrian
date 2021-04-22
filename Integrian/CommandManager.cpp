#include "pch.h"
#include "CommandManager.h"
#include "Command.h"
#include "ExceptionHandler.h"
#include "InputManager.h"
#include "Logger.h"

Integrian::CommandManager::CommandManager(InputManager& inputManager)
	: m_InputManager{ inputManager }
{
}

Integrian::CommandManager::~CommandManager()
{
	m_Commands.clear();
	m_CommandsToBeDeleted.clear();
}

void Integrian::CommandManager::LinkCommandToInput(const GameInput& gameInput, const std::string& commandName, const State keyState, const uint8_t controllerIndex)
{
#ifdef _DEBUG
	UMapIterator it{ m_Commands.find(commandName) };
	if (it != m_Commands.cend())
		m_InputManager.AddCommand(gameInput, it->second, keyState, controllerIndex);
	else
		Logger::LogWarning("LinkCommandToInput() did not find a command with name: " + commandName + "\n");
#else
	InputManager::GetInstance().AddCommand(gameInput, m_pCommands.find(commandName)->second, keyState, controllerIndex);
#endif // _DEBUG
}

void Integrian::CommandManager::RemoveCommand(const std::string& commandName)
{
#ifdef _DEBUG
	const UMapIterator it{ m_Commands.find(commandName) };
	if (it != m_Commands.end())
	{
		m_CommandsToBeDeleted.push_back(it->second); // to be deleted later
		m_InputManager.RemoveCommand(it->second);
		m_Commands.erase(commandName);
	}
	else
		Logger::LogWarning("RemoveCommand() did not find a command with name: " + commandName + "\n");
#else
	const UMapIterator it{ m_pCommands.find(commandName) };
	if (it != m_pCommands.end())
	{
		m_pCommandsToBeDeleted.push_back(it->second);
		InputManager::GetInstance().RemoveCommand(it->second);
		m_pCommands.erase(commandName);
	}
#endif // _DEBUG
}
