#include "pch.h"
#include "CommandManager.h"
#include "Command.h"
#include "ExceptionHandler.h"
#include "InputManager.h"

Integrian::CommandManager::CommandManager(const char* pFile, const int line)
{
	if (m_IsInstantiated)
		throw StaticInstanceAlreadyCreated{ pFile, line};

	m_IsInstantiated = true;
}

Integrian::CommandManager::~CommandManager()
{
	for (Command* pCommand : m_pCommands)
		SafeDelete(pCommand);
}

void Integrian::CommandManager::LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	InputManager::GetInstance().AddCommand(gameInput, pCommand, keyState, controllerIndex);
}

void Integrian::CommandManager::RemoveCommand(Command* pCommand)
{
	
}
