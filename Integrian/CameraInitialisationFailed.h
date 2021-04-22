#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef INTEGRIAN_CAMERAINITIALISATIONFAILEDEXCEPTION_H
#define INTEGRIAN_CAMERAINITIALISATIONFAILEDEXCEPTION_H

#include "Logger.h" // Logger

namespace Integrian
{
	class CameraInitialisationFailedException final
	{
	public:
		CameraInitialisationFailedException()
		{
			Logger::LogSevereError("EXCEPTION: App::InitializeCamera() called in App::FinishInitialisationOfApp() failed");
		}
	};
}

#endif // !ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H