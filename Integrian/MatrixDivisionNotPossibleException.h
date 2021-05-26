#pragma once

#ifndef INTEGRIAN_MATRIXDIVISIONNOTPOSSIBLEEXCEPTION_H
#define INTEGRIAN_MATRIXDIVISIONNOTPOSSIBLEEXCEPTION_H

#include "Logger.h"

namespace Integrian
{
	class MatrixDivisionNotPossibleException final
	{
	public:
		MatrixDivisionNotPossibleException()
		{
			Logger::LogSevereError("EXCEPTION: Matrix division is not possible because matrix has no inverse!\n");
		}
	};
}

#endif // !INTEGRIAN_MATRIXDIVISIONNOTPOSSIBLEEXCEPTION_H