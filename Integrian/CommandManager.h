#pragma once
#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include <vector>
#include "GameInput.h"
#include <type_traits> // std::is_base_of
#include <algorithm> // std::find
#include "Singleton.h"

namespace Integrian
{
	class Command;
	class CommandManager final : public Singleton<CommandManager>
	{
	public:
		CommandManager() = default;
		~CommandManager();

		Command* AddCommand(Command* pCommand);
		void LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void RemoveCommand(Command* pCommand);

	private:
		friend class Singleton<CommandManager>;

		std::vector<Command*> m_pCommands;
		};
	}

#endif // !INTEGRIAN_COMMANDMANAGER_H