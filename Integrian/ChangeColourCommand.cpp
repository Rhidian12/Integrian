#include "ChangeColourCommand.h"
#include "ScoreComponent.h"

Integrian::ChangeColourCommand::ChangeColourCommand(ScoreComponent* pScoreComponent)
	: m_pScoreComponent{ pScoreComponent }
{
}

void Integrian::ChangeColourCommand::Execute()
{
	m_pScoreComponent->ChangeScore(TypeOfGettingScore::ColourChange);
}
