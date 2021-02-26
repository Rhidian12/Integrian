#include "DefeatCoilyCommand.h"
#include "ScoreComponent.h"

Integrian::DefeatCoilyCommand::DefeatCoilyCommand(ScoreComponent* pScoreComponent)
	: m_pScoreComponent{ pScoreComponent }
{
}

void Integrian::DefeatCoilyCommand::Execute()
{
	m_pScoreComponent->ChangeScore(TypeOfGettingScore::CoilyDefeated);
}
