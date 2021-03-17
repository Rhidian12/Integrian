#include "pch.h"
#include "Logger.h"
#include <Windows.h>
#include "StaticInstanceAlreadyCreated.h"

// Reference: https://stackoverflow.com/questions/8765938/colorful-text-using-printf-in-c
// Reference: https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute
// Reference: https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#character-attributes
// Reference: https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c#:~:text=The%20simplest%20way%20you%20can,code%20for%20the%20text%20color.

// BOOL WINAPI SetConsoleTextAttribute(
// 	_In_ HANDLE hConsoleOutput,
//	_In_ WORD   wAttributes
// );
// 

// 0 = black
// 1 = intense blue
// 2 = green
// 3 = light blue
// 4 = red
// 5 = purple
// 6 = yellow
// 7 = white
// 8 = grey
// 9 = blue
// 10 = light green
// 11 = very light blue
// 12 = light red
// 13 = lighter purple
// 14 = very light yellow
// 15 = intense white

Integrian::Logger::Logger(const char* pFile, const int line)
{
	if (m_IsInstantiated)
		throw StaticInstanceAlreadyCreated{ pFile, line };

	m_IsInstantiated = true;
}

void Integrian::Logger::Log(const std::string& message, const ErrorLevel level) const
{
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (level)
	{
	case ErrorLevel::noWarning:
		SetConsoleTextAttribute(hConsole, 2);
		break;
	case ErrorLevel::warning:
		SetConsoleTextAttribute(hConsole, 6);
		break;
	case ErrorLevel::error:
		SetConsoleTextAttribute(hConsole, 12);
		break;
	case ErrorLevel::severeError:
		SetConsoleTextAttribute(hConsole, 4);
		break;
	}
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // set text back to white
}