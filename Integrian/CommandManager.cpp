#include "pch.h"
#include "CommandManager.h"
#include "Command.h"
#include "ExceptionHandler.h"
#include "InputManager.h"
#include <algorithm> // std::find

Integrian::CommandManager::CommandManager(const char* pFile, const int line)
{
	if (m_IsInstantiated)
		throw StaticInstanceAlreadyCreated{ pFile, line };

	m_IsInstantiated = true;
}

Integrian::CommandManager::~CommandManager()
{
	for (Command* pCommand : m_pCommands)
		SafeDelete(pCommand);
	m_pCommands.clear();
}

void Integrian::CommandManager::LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	InputManager::GetInstance().AddCommand(gameInput, pCommand, keyState, controllerIndex);
}

void Integrian::CommandManager::AddCommand(Command* pCommand)
{
	m_pCommands.push_back(pCommand);
}

void Integrian::CommandManager::RemoveCommand(Command*)
{
	//TODO: Remove Commands (event queue)!
	//delete *(std::find(m_pCommands.begin(), m_pCommands.end(), pCommand));
}
