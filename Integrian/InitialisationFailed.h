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
			Logger::GetInstance().Log("ERROR: Initialisation Failed", ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_INITIALISATIONFAILEDEXCEPTION_H