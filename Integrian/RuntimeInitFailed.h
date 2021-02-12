#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_RUNTIMEINITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_RUNTIMEINITIALISATIONFAILEDEXCEPTION_H

namespace Engine
{
	class RuntimeInitialisationFailed final
	{
	public:
		RuntimeInitialisationFailed()
		{
			std::cerr << "EXCEPTION: Something went wrong in App::FinishInitialisationOfApp()";
		}
	};
}

#endif // !ENGINE_RUNTIMEINITIALISATIONFAILEDEXCEPTION_H