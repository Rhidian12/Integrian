#pragma once
// ====================================
// Author: Rhidian De Wit
// February 2021 ---- Last Edited: February 2021
// ====================================
#ifndef ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H
#define ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H

namespace Engine
{
	class CameraInitialisationFailedException final
	{
	public:
		CameraInitialisationFailedException()
		{
			std::cerr << "EXCEPTION: App::InitializeCamera() called in App::FinishInitialisationOfApp() failed";
		}
	};
}

#endif // !ENGINE_CAMERAINITIALISATIONFAILEDEXCEPTION_H