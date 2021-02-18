#include "pch.h"
#include "CommandManager.h"
#include "Command.h"

Integrian::CommandManager::~CommandManager()
{
	for (Command* pCommand : m_pCommands)
		SAFE_DELETE(pCommand);
}

void Integrian::CommandManager::AddCommand(Command* pCommand)
{
	const std::vector<Command*>::const_iterator isCommandAlreadyInList =
		std::find_if(m_pCommands.cbegin(), m_pCommands.cend(), [pCommand](Command* pC)->bool
			{
				return pCommand == pC;
			});
	if (isCommandAlreadyInList != m_pCommands.cend())
	{
		Logger::GetInstance().Log(typeid(*pCommand).name(), ErrorLevel::severeError);
		Logger::GetInstance().Log(" was already added!\n", ErrorLevel::severeError);
	}
	else
		m_pCommands.push_back(pCommand);
}
