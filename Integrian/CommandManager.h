#pragma once
#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include "GameInput.h" // GameInput
#include "Singleton.h" // Singleton

namespace Integrian
{
	class Command;
	class CommandManager final : public Singleton<CommandManager>
	{
	public:
		CommandManager() = default;
		~CommandManager();

		/* 
		Add a command by giving it a name which can be used to later link it to input and/or remove it
		The Command parameter must be a subclass of Command
		Storing the commands is not necessary, since adding the command here will ensure that it is deleted at the end of the application
		*/
		void AddCommand(const std::string& identifier, Command* pCommand);

		/* This links a command to a KeyboardInput, ControllerInput or MouseInput */
		void LinkCommandToInput(const GameInput& gameInput, const std::string& commandName, const State keyState, const uint8_t controllerIndex = 0);
		
		/* This removes a command from both the CommandManager and all inputs linked to it */
		void RemoveCommand(const std::string& commandName);

		/* 
		Returns the command with the given identifier
		Returns a nullpointer when no command with that identifier can be found
		*/
		Command* GetCommand(const std::string& identifier);

	private:
		friend class Singleton<CommandManager>;

		std::unordered_map<std::string, Command*> m_pCommands{};
		std::vector<Command*> m_pCommandsToBeDeleted{};

		using StringCommandPair = std::pair<std::string, Command*>;
		using UMapIterator = std::unordered_map<std::string, Command*>::iterator;
	};
}

#endif // !INTEGRIAN_COMMANDMANAGER_H