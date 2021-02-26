#pragma once
#ifndef INTEGRIAN_DISKSREMAININGCOMMAND_H
#define INTEGRIAN_DISKSREMAININGCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class ScoreComponent;
	class DisksRemainingCommand final : public Command
	{
	public:
		DisksRemainingCommand(ScoreComponent* pScoreComponent);
		virtual ~DisksRemainingCommand() = default;

		virtual void Execute() override;

	private:
		ScoreComponent* m_pScoreComponent;
	};
}

#endif // !INTEGRIAN_DISKSREMAININGCOMMAND_H