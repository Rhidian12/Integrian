#pragma once
// ====================================
// Author: Rhidian De Wit
// March 2021 ---- Last Edited: March 2021
// ====================================
#ifndef ENGINE_COMMANDNOTCREATEDBYMANAGER_H
#define ENGINE_COMMANDNOTCREATEDBYMANAGER_H

#include "ServiceLocator.h"

namespace Integrian
{
	class CommandNotCreatedByManager final
	{
	public:
		CommandNotCreatedByManager()
		{
<<<<<<< HEAD
			ServiceLocator::GetInstance().GetLogger().Log("ERROR: Command not created through CommandManager::CreateCommand()\n", ErrorLevel::severeError);
=======
			Logger::GetInstance().Log("ERROR: Initialisation Failed\n", ErrorLevel::severeError);
>>>>>>> parent of 9f32a8a (Made CommandManager BUT NEEDS EVENT QUEUE TO BE FINISHED)
		}
	};
}

#endif // !ENGINE_COMMANDNOTCREATEDBYMANAGER_H