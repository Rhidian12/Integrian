#pragma once
#ifndef INTEGRIAN_KILLCOMMAND_H
#define INTEGRIAN_KILLCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class HealthComponent;
	class KillCommand final : public Command
	{
	public:
		KillCommand(HealthComponent* pHealth);

		virtual void Execute() override;

	private:
		HealthComponent* m_pHealthComponent;
	};
}

#endif // !INTEGRIAN_KILLCOMMAND_H