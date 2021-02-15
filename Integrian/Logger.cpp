#include "pch.h"
#include "Logger.h"
#include <windows.h>

// Reference: https://stackoverflow.com/questions/8765938/colorful-text-using-printf-in-c
// Reference: https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
// Reference: https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes

// BOOL WINAPI SetConsoleTextAttribute(
// 	_In_ HANDLE hConsoleOutput,
//	_In_ WORD   wAttributes
// );
// 
// ReSharper disable once CppMemberFunctionMayBeStatic
void Integrian::Logger::Log(const std::string& message, const ErrorLevel level) const
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (level)
	{
	case ErrorLevel::noWarning:
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		break;
	case ErrorLevel::warning:
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		break;
	case ErrorLevel::error:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		break;
	case ErrorLevel::severeError:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	}
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // 7 == non-intense white
}