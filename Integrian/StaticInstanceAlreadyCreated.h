#pragma once
#ifndef ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H
#define ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H

#include "ServiceLocator.h"

namespace Integrian
{
	class StaticInstanceAlreadyCreated final
	{
	public:
		StaticInstanceAlreadyCreated(const char* pFile, const int line)
		{
			ServiceLocator::GetInstance().GetLogger().Log("EXCEPTION: A static instance was created twice in file: ", ErrorLevel::severeError);
			ServiceLocator::GetInstance().GetLogger().Log(pFile, ErrorLevel::severeError);
			ServiceLocator::GetInstance().GetLogger().Log(" at line: ", ErrorLevel::severeError);
			ServiceLocator::GetInstance().GetLogger().Log(std::to_string(line), ErrorLevel::severeError);
		}
	};
}

#endif // !ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H