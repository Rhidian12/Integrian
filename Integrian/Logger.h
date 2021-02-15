#pragma once
#ifndef INTEGRIAN_LOGGER_H
#define INTEGRIAN_LOGGER_H

#include "Singleton.h"
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
	class Logger final : public Singleton<Logger>
	{
	public:
		void Log(const std::string& message, const ErrorLevel level) const;

	private:
		Logger() = default;
		friend class Singleton<Logger>;
	};
}

#endif