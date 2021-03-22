#pragma once

#ifndef INTEGRIAN_ILISTENER_H
#define INTEGRIAN_ILISTENER_H

#include "Event.h"

namespace Integrian
{
	class IListener abstract
	{
	public:
		virtual ~IListener() = default;

		virtual bool OnEvent(const Event&) = 0;
	};
}

#endif // !INTEGRIAN_ILISTENER_H
