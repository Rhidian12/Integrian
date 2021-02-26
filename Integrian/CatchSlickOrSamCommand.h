#pragma once
#ifndef INTEGRIAN_CATCHSLICKORSAMCOMMAND_H
#define INTEGRIAN_CATCHSLICKORSAMCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class ScoreComponent;
	class CatchSlickOrSamCommand final : public Command
	{
	public:
		CatchSlickOrSamCommand(ScoreComponent* pScoreComponent);
		virtual ~CatchSlickOrSamCommand() = default;

		virtual void Execute() override;

	private:
		ScoreComponent* m_pScoreComponent;
	};
}

#endif // !INTEGRIAN_CATCHSLICKORSAMCOMMAND_H