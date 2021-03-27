#include "pch.h"
#include "CommandManager.h"
#include "Command.h"
#include "ExceptionHandler.h"
#include "InputManager.h"
#include "Logger.h"

Integrian::CommandManager::~CommandManager()
{
	for (StringCommandPair stringCommandPair : m_pCommands)
		SafeDelete(stringCommandPair.second);

	for (Command* pCommand : m_pCommandsToBeDeleted)
		SafeDelete(pCommand);
}

void Integrian::CommandManager::AddCommand(const std::string& identifier, Command* pCommand)
{
#ifdef _DEBUG
	if (m_pCommands.find(identifier) == m_pCommands.cend())
		m_pCommands.insert(std::make_pair(identifier, pCommand));
	else
		// the command has already been added. Add it nonetheless, but log a warning
		Logger::LogWarning("Command was already added!\n");
#else
	m_pCommands.insert(std::make_pair(identifier, pCommand));
#endif // _DEBUG
}

void Integrian::CommandManager::LinkCommandToInput(const GameInput& gameInput, const std::string& commandName, const State keyState, const uint8_t controllerIndex)
{
#ifdef _DEBUG
	UMapIterator it{ m_pCommands.find(commandName) };
	if (it != m_pCommands.cend())
		InputManager::GetInstance().AddCommand(gameInput, it->second, keyState, controllerIndex);
	else
		Logger::LogWarning("LinkCommandToInput() did not find a command with name: " + commandName + "\n");
#else
	InputManager::GetInstance().AddCommand(gameInput, m_pCommands.find(commandName)->second, keyState, controllerIndex);
#endif // _DEBUG
}

void Integrian::CommandManager::RemoveCommand(const std::string& commandName)
{
#ifdef _DEBUG
	const UMapIterator it{ m_pCommands.find(commandName) };
	if (it != m_pCommands.end())
	{
		m_pCommandsToBeDeleted.push_back(it->second); // to be deleted later
		InputManager::GetInstance().RemoveCommand(it->second);
		m_pCommands.erase(commandName);
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

Integrian::Command* Integrian::CommandManager::GetCommand(const std::string& identifier)
{
#ifdef _DEBUG
	UMapIterator it{ m_pCommands.find(identifier) };
	if (it != m_pCommands.end())
		return it->second;
	else
	{
		Logger::LogWarning("GetCommand() did not find a command with name: " + identifier + "\n");
		return nullptr;
	}
#else
	UMapIterator it{ m_pCommands.find(identifier) };
	if (it != m_pCommands.end())
		return it->second;
	else
		return nullptr;
#endif
}
