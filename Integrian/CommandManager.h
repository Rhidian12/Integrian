#pragma once
#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include <vector>
#include "GameInput.h"
#include <type_traits> // std::is_base_of
#include <algorithm> // std::find

namespace Integrian
{
	class Command;
	class CommandManager final
	{
	public:
		CommandManager(const char* pFile, const int pLine);
		~CommandManager();

		template<typename Type>
		Type* CreateCommand(Type* pCommand, char* pFile = __FILE__, const int line = __LINE__)
		{
			if constexpr (std::is_base_of_v<Command, Type>)
			{
#ifdef _DEBUG
				if (std::find(m_pCommands.cbegin(), m_pCommands.cend(), pCommand) != m_pCommands.cend())
				{
					// the command has already been added. Add it nonetheless, but log a warning
					m_pCommands.push_back(pCommand);
					Logger::GetInstance().Log("Command was already added!", ErrorLevel::warning);
				}
#else
				m_pCommands.push_back(pCommand);
#endif // _DEBUG
			}
			else // We're not adding a Command, so just log an error
			{
				Logger& logger{ Logger::GetInstance() }; // TODO: Jfc Rhidian, please. I M P R O V E T H I S L O G G E R
				logger.Log("CreateCommand() called from file: ", ErrorLevel::error);
				logger.Log(pFile, ErrorLevel::error);
				logger.Log(" on line: ", ErrorLevel::error);
				logger.Log(std::to_string(line), ErrorLevel::error);
				logger.Log(" was not given a subclassed Command as argument!\n", ErrorLevel::error);
			}
		}
		void LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void RemoveCommand(Command* pCommand);

	private:
		inline static bool m_IsInstantiated{ false };
		std::vector<Command*> m_pCommands;
	};
}

#endif // !INTEGRIAN_COMMANDMANAGER_H