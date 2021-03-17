#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_INITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_INITIALISATIONFAILEDEXCEPTION_H

#include "ServiceLocator.h"

namespace Integrian
{
	class InitialisationFailedException final
	{
	public:
		InitialisationFailedException()
		{
			ServiceLocator::GetInstance().GetLogger().Log("ERROR: Initialisation Failed\n", ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_INITIALISATIONFAILEDEXCEPTION_H