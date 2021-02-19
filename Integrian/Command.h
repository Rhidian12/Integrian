#pragma once

#ifndef INTEGRIAN_COMMAND_H
#define INTEGRIAN_COMMAND_H

namespace Integrian
{
	class GameObject;
	class Command abstract
	{
	public:
		Command();
		Command(GameObject* actor);
		virtual ~Command() = default;

		virtual void Execute() = 0;
		
	protected:
		GameObject* m_Actor;
	};
}

#endif //INTEGRIAN_COMMAND_H