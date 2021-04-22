#pragma once

#ifndef INTEGRIAN_COMMANDMANAGER_H
#define INTEGRIAN_COMMANDMANAGER_H

#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include "GameInput.h" // GameInput
#include <functional> // std::function
#include "InputManager.h" // InputManager
#include <type_traits> // std::is_assignable_v

namespace Integrian
{
	class CommandManager final
	{
	public:
		~CommandManager();

		/*
		Add a command by giving it a name which can be used to later link it to input and/or remove it
		The Command parameter must be a subclass of Command
		Storing the commands is not necessary, since adding the command here will ensure that it is deleted at the end of the application
		*/
		template<typename Lambda>
		void AddCommand(const std::string& identifier, Lambda&& lambda)
		{
			if constexpr (std::is_assignable_v<std::function<void()>, Lambda>)
			{
#ifdef _DEBUG
				if (m_Commands.find(identifier) == m_Commands.cend())
					m_Commands.insert(std::make_pair(identifier, lambda));
				else
					Logger::LogWarning("Command was already added!\n"); // the command has already been added.
#else
				m_pCommands.insert(std::make_pair(identifier, lambda));
#endif // _DEBUG
			}
			else
				static_assert(AlwaysFalse(), "The second argument of CommandManager::AddCommand was not a lambda");
		}

		/* This links a command to a KeyboardInput, ControllerInput or MouseInput */
		void LinkCommandToInput(const GameInput& gameInput, const std::string& commandName, const State keyState, const uint8_t controllerIndex = 0);

		/* This removes a command from both the CommandManager and all inputs linked to it */
		void RemoveCommand(const std::string& commandName);

		/*
		Returns the command with the given identifier
		Returns a nullpointer when no command with that identifier can be found
		*/
		template<typename Lambda>
		Lambda GetCommand(const std::string& identifier)
		{
#ifdef _DEBUG
			UMapIterator it{ m_Commands.find(identifier) };
			if (it != m_Commands.end())
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

	private:
		friend struct App_Info;
		CommandManager(InputManager& inputManager);

		std::unordered_map<std::string, std::function<void()>> m_Commands{};
		std::vector<std::function<void()>> m_CommandsToBeDeleted{};

		InputManager& m_InputManager;

		using StringCommandPair = std::pair<std::string, std::function<void()>>;
		using UMapIterator = std::unordered_map<std::string, std::function<void()>>::iterator;
	};
}

#endif // !INTEGRIAN_COMMANDMANAGER_H