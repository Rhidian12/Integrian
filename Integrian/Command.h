#pragma once

#ifndef INTEGRIAN_COMMAND_H
#define INTEGRIAN_COMMAND_H

#include "GameObject.h"

namespace Integrian
{
	class Command abstract
	{
	public:
		Command();
		Command(const GameObject& actor);
		virtual ~Command() = default;

		virtual void Execute() = 0;
		
	protected:
		GameObject m_Actor;
	};
}

#endif //INTEGRIAN_COMMAND_H