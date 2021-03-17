#pragma once
#ifndef ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H
#define ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H
#include <iostream>
namespace Integrian
{
	class StaticInstanceAlreadyCreated final
	{
	public:
		StaticInstanceAlreadyCreated(const char* pFile, const int line)
		{
			std::cerr << "EXCEPTION: A static instance was created twice in file: " << pFile << "at line: " << line << std::endl;
		}
	};
}

#endif // !ENGINE_STATICINSTANCEALREADYCREATEDEXCEPTION_H