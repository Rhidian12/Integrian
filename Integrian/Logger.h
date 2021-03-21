#pragma once
#ifndef INTEGRIAN_LOGGER_H
#define INTEGRIAN_LOGGER_H

#include <string>
#include "Singleton.h"

enum class ErrorLevel
{
	noWarning		= 0,
	warning			= 1,
	error			= 2,
	severeError		= 3
};

namespace Integrian
{
	class Logger final : public Singleton<Logger> // TODO: Make this just a static class, it doesn't need to store data
	{
	public:
		Logger() = default;
		void Log(const std::string& message, const ErrorLevel level) const;

	private:
	};
}

#endif