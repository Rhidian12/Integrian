#pragma once

#ifndef INTEGRIAN_DIVISIONBYZERONOTPOSSIBLEXCEPTION_H
#define INTEGRIAN_DIVISIONBYZERONOTPOSSIBLEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class DivisionByZeroNotPossible final
	{
	public:
		DivisionByZeroNotPossible()
		{
			Logger::LogSevereError("EXCEPTION: Division by zero is not possible!\n");
		}
	};
}

#endif // !INTEGRIAN_DIVISIONBYZERONOTPOSSIBLEXCEPTION_H