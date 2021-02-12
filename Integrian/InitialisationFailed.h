#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_INITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_INITIALISATIONFAILEDEXCEPTION_H

namespace Integrian
{
	class InitialisationFailedException final
	{
	public:
		InitialisationFailedException()
		{
			std::cerr << "EXCEPTION: Initialisation of app failed" << std::endl;
		}
	};
}

#endif // !ENGINE_INITIALISATIONFAILEDEXCEPTION_H