#include "pch.h"
#include "CommandManager.h"
#include "Command.h"
#include "ExceptionHandler.h"
#include "InputManager.h"
#include "Logger.h"

Integrian::CommandManager::~CommandManager()
{
	for (Command* pCommand : m_pCommands)
		SafeDelete(pCommand);
}

Integrian::Command* Integrian::CommandManager::AddCommand(Command* pCommand)
{
#ifdef _DEBUG
	if (std::find(m_pCommands.cbegin(), m_pCommands.cend(), pCommand) != m_pCommands.cend())
	{
		// the command has already been added. Add it nonetheless, but log a warning
		m_pCommands.push_back(pCommand);
		Logger::LogWarning("Command was already added!\n");
	}
#else
	m_pCommands.push_back(pCommand);
#endif // _DEBUG

	return pCommand;
}

void Integrian::CommandManager::LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	InputManager::GetInstance().AddCommand(gameInput, pCommand, keyState, controllerIndex);
}

void Integrian::CommandManager::RemoveCommand(Command* pCommand)
{
	(void)pCommand;
	// TODO: implement this!
}
