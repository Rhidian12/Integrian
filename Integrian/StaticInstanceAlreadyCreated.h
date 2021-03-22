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
			Logger::LogSevereError(std::string{ "EXCEPTION: A static instance was created twice in file: " } + pFile + " at line: " + std::to_string(line));
		}
	};
}

#endif // !ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H