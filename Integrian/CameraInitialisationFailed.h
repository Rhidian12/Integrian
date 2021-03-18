#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class CameraInitialisationFailedException final
	{
	public:
		CameraInitialisationFailedException()
		{
			Logger::GetInstance().Log("EXCEPTION: App::InitializeCamera() called in App::FinishInitialisationOfApp() failed", ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H