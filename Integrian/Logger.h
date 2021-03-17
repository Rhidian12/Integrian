#pragma once
#ifndef INTEGRIAN_LOGGER_H
#define INTEGRIAN_LOGGER_H

#include <string>

enum class ErrorLevel
{
	noWarning		= 0,
	warning			= 1,
	error			= 2,
	severeError		= 3
};

namespace Integrian
{
	class Logger final
	{
	public:
		Logger(const char* pFile, const int line);
		void Log(const std::string& message, const ErrorLevel level) const;

	private:
		inline static bool m_IsInstantiated{};
	};
}

#endif