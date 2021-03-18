#pragma once
#ifndef ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H
#define ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class StaticInstanceAlreadyCreated final
	{
	public:
		StaticInstanceAlreadyCreated(const char* pFile, const int line)
		{
			Logger& logger{ Logger::GetInstance() };
			logger.Log("EXCEPTION: A static instance was created twice in file: ", ErrorLevel::severeError);
			logger.Log(pFile, ErrorLevel::severeError);
			logger.Log(" at line: ", ErrorLevel::severeError);
			logger.Log(std::to_string(line), ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H