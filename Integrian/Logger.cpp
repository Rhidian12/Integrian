#include "IntegrianPCH.h" // precompiled header
#include "Logger.h" // Header

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

void Integrian::Logger::LogNoWarning(const std::string& message)
{
#ifdef _DEBUG
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else 
	(void)message;
#endif // _DEBUG
}

void Integrian::Logger::LogWarning(const std::string& message)
{
#ifdef _DEBUG
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 6);
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
	(void)message;
#endif // _DEBUG
}

void Integrian::Logger::LogError(const std::string& message)
{
#ifdef _DEBUG
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
	(void)message;
#endif // _DEBUG
}

void Integrian::Logger::LogSevereError(const std::string& message)
{
#ifdef _DEBUG
	const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << message;
	SetConsoleTextAttribute(hConsole, 7); // set text back to white
#else
	(void)message;
#endif // _DEBUG
}

void Integrian::Logger::SetDebugOnly(const bool debugOnly)
{
	m_DebugOnly = debugOnly;
}
