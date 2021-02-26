#pragma once
#ifndef INTEGRIAN_CHANGECOLOURCOMMAND_H
#define INTEGRIAN_CHANGECOLOURCOMMAND_H

#include "Command.h"

namespace Integrian
{
	class ScoreComponent;
	class ChangeColourCommand final : public Command
	{
	public:
		ChangeColourCommand(ScoreComponent* pScoreComponent);
		virtual ~ChangeColourCommand() = default;

		virtual void Execute() override;
	
	private:
		ScoreComponent* m_pScoreComponent;
	};
}

#endif // !INTEGRIAN_CHANGECOLOURCOMMAND_H