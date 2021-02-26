#include "CatchSlickOrSamCommand.h"
#include "ScoreComponent.h"

Integrian::CatchSlickOrSamCommand::CatchSlickOrSamCommand(ScoreComponent* pScoreComponent)
	: m_pScoreComponent{ pScoreComponent }
{
}

void Integrian::CatchSlickOrSamCommand::Execute()
{
	m_pScoreComponent->ChangeScore(TypeOfGettingScore::CatchingSlickAndSam);
}
