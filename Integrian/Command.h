#pragma once

#ifndef INTEGRIAN_COMMAND_H
#define INTEGRIAN_COMMAND_H

namespace Integrian
{
	class GameObject;
	class Command abstract
	{
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
		
	protected:
		Command() = default;
	};
}

#endif //INTEGRIAN_COMMAND_H