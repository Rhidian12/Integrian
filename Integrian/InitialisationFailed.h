#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_INITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_INITIALISATIONFAILEDEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class InitialisationFailedException final
	{
	public:
		InitialisationFailedException()
		{
			Logger::LogSevereError("ERROR: Initialisation Failed\n");
		}
	};
}

#endif // !ENGINE_INITIALISATIONFAILEDEXCEPTION_H