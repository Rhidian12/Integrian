#pragma once
#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include <vector>
#include "GameInput.h"
#include <algorithm> // std::find

namespace Integrian
{
	class Command;
	class CommandManager final
	{
	public:
		CommandManager(const char* pFile, const int pLine);
		~CommandManager();

		void AddCommand(Command* pCommand);
		void LinkCommandToInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		void RemoveCommand(Command* pCommand);

	private:
		inline static bool m_IsInstantiated{ false };
		std::vector<Command*> m_pCommands;
	};
}

#endif // !INTEGRIAN_COMMANDMANAGER_H