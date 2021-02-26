#pragma once
#ifndef INTEGRIAN_DEFEATCOILYCOMMAND_H
#define INTEGRIAN_DEFEATCOILYCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class ScoreComponent;
	class DefeatCoilyCommand final : public Command
	{
	public:
		DefeatCoilyCommand(ScoreComponent* pScoreComponent);
		virtual ~DefeatCoilyCommand() = default;

		virtual void Execute() override;

	private:
		ScoreComponent* m_pScoreComponent;
	};
}

#endif // !INTEGRIAN_DEFEATCOILYCOMMAND_H