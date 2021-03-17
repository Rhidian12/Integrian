#include "Command.h"
#include "Logger.h"

Integrian::Command::Command(char* pFile)
	: Command{ nullptr }
{
	if (pFile != "CommandManager.cpp")
	{
		Logger& logger{ Logger::GetInstance() };
		logger.Log("", ErrorLevel::error);
	}
}
