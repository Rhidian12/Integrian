#pragma once

#ifndef INTEGRIAN_APP_INFO_H
#define INTEGRIAN_APP_INFO_H

#include "EventQueue.h" // EventQueue
#include "CommandManager.h" // CommandManager
#include "InputManager.h" // InputManager

namespace Integrian
{
	struct App_Info final
	{
		App_Info()
			: eventQueue{}
			, inputManager{ eventQueue }
			, commandManager{ inputManager }
		{

		}
		~App_Info() = default;

		App_Info(const App_Info&) = delete;
		App_Info(App_Info&&) = delete;
		App_Info& operator=(const App_Info&) = delete;
		App_Info& operator=(App_Info&&) = delete;

		EventQueue eventQueue;
		InputManager inputManager;
		CommandManager commandManager;
	};
}

#endif // !INTEGRIAN_APP_INFO_H
