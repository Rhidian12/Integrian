#pragma once
#ifndef INTEGRIAN_LOGGER_H
#define INTEGRIAN_LOGGER_H

#include <string> // std::String

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
		static void LogNoWarning(const std::string& message);
		static void LogWarning(const std::string& message);
		static void LogError(const std::string& message);
		static void LogSevereError(const std::string& message);

		static void SetDebugOnly(const bool debugOnly);

	private:
		inline static bool m_DebugOnly{};
	};
}

#endif