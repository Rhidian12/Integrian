#pragma once

#ifndef INTEGRIAN_ILISTENER_H
#define INTEGRIAN_ILISTENER_H

#include "IntegrianPCH.h"
#include "Event.h" // Event

namespace Integrian
{
	class INTEGRIAN_API IListener
	{
	public:
		virtual ~IListener() = default;

		virtual bool OnEvent(const Event&) = 0;

		bool m_IsActive;
	};
}

#endif // !INTEGRIAN_ILISTENER_H
