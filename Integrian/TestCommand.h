#pragma once
#ifndef INTEGRIAN_RESETFPSCOMMAND_H
#define INTEGRIAN_RESETFPSCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class FPSComponent;
	class TestCommand final : public Command
	{
	public:
		TestCommand(FPSComponent* pFPSComponent);
		virtual ~TestCommand() = default;

		virtual void Execute() override;

	private:
		FPSComponent* m_pFPSComponent;
	};
}

#endif //INTEGRIAN_RESETFPSCOMMAND_H