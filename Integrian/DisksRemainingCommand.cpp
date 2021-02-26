#include "DisksRemainingCommand.h"
#include "ScoreComponent.h"

Integrian::DisksRemainingCommand::DisksRemainingCommand(ScoreComponent* pScoreComponent)
	: m_pScoreComponent{ pScoreComponent }
{
}

void Integrian::DisksRemainingCommand::Execute()
{
	m_pScoreComponent->ChangeScore(TypeOfGettingScore::RemainingDiscs);
}
