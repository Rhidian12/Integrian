#pragma once
#ifndef INTEGRIAN_RESETFPSCOMMAND_H
#define INTEGRIAN_RESETFPSCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class FPSComponent;
	class ResetFPSCommand final : public Command
	{
	public:
		ResetFPSCommand(FPSComponent* pFPSComponent, const GameObject& actor);
		virtual ~ResetFPSCommand() = default;

		virtual void Execute() override;

	private:
		FPSComponent* m_pFPSComponent;
	};
}

#endif //INTEGRIAN_RESETFPSCOMMAND_H