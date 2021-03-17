#pragma once
// ====================================
// Author: Rhidian De Wit
// March 2021 ---- Last Edited: March 2021
// ====================================
#ifndef ENGINE_COMMANDNOTCREATEDBYMANAGER_H
#define ENGINE_COMMANDNOTCREATEDBYMANAGER_H

#include "Logger.h"

namespace Integrian
{
	class CommandNotCreatedByManager final
	{
	public:
		CommandNotCreatedByManager()
		{
			Logger::GetInstance().Log("ERROR: Initialisation Failed\n", ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_COMMANDNOTCREATEDBYMANAGER_H