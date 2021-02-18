#pragma once

#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include "Singleton.h"
#include <vector>
#include "Logger.h"

namespace Integrian
{
	class Command;
	class CommandManager final : public Singleton<CommandManager>
	{
	public:
		virtual ~CommandManager();

		void AddCommand(Command* pCommand);

		template<typename Type>
		[[nodiscard]] Type* GetCommandByType() const
		{
			for (Command* pCommand : m_pCommands)
				if (typeid(*pCommand) == typeid(Type))
					return static_cast<Type*>(pCommand);

			Logger::GetInstance().Log("GetCommandByType returned a nullptr\n", ErrorLevel::warning);
			return nullptr;
		}
		template<typename Type>
		[[nodiscard]] std::vector<Type*> GetAllCommandsByType() const
		{
			std::vector<Command*> pAllCommandsOfType;

			for (Command* pCommand : m_pCommands)
				if (typeid(*pCommand) == typeid(Type))
					pAllCommandsOfType.push_back(pCommand);

			Logger::GetInstance().Log("GetAllCommandsByType returned an empty list\n", ErrorLevel::warning);
			return pAllCommandsOfType;
		}
		template<typename Type>
		[[nodiscard]] std::vector<Type*>&& GetAllCommandsByType() const
		{
			std::vector<Command*> pAllCommandsOfType;

			for (Command* pCommand : m_pCommands)
				if (typeid(*pCommand) == typeid(Type))
					pAllCommandsOfType.push_back(pCommand);

			Logger::GetInstance().Log("GetAllCommandsByType returned an empty list\n", ErrorLevel::warning);
			return std::move(pAllCommandsOfType);
		}

	private:
		friend class Singleton<CommandManager>;
		CommandManager() = default;

		std::vector<Command*> m_pCommands;
	};
}

#endif //INTEGRIAN_COMMANDMANAGER_H