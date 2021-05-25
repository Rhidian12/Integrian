#pragma once

#ifndef INTEGRIAN_MAGNITUDEZEROEXCEPTION_H
#define INTEGRIAN_MAGNITUDEZEROEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class MagnitudeZeroException final
	{
	public:
		MagnitudeZeroException()
		{
			Logger::LogSevereError("EXCEPTION: Normalize() parameter was vector with magnitude 0!\n");
		}
	};
}

#endif