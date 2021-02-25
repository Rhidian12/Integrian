#pragma once
#ifndef INTEGRIAN_KILLCOMMAND_H
#define INTEGRIAN_KILLCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class ActorComponent;
	class TextComponent;
	class KillCommand final : public Command
	{
	public:
		KillCommand(ActorComponent* pActor);

		virtual void Execute() override;

	private:
		ActorComponent* m_pActor;
	};
}

#endif // !INTEGRIAN_KILLCOMMAND_H