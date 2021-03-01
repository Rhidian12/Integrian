#include "ScoreComponent.h"
#include "Subject.h"

Integrian::ScoreComponent::ScoreComponent(const uint64_t maxScore, const uint64_t currentScore)
	: m_CurrentScore{ currentScore }
	, m_MaxScore{ maxScore }
	, m_pSubject{ std::make_unique<Subject>() }
{
}

void Integrian::ScoreComponent::ChangeScore(const TypeOfGettingScore score)
{
	if (m_CurrentScore < m_MaxScore)
	{
		m_CurrentScore += static_cast<std::underlying_type<TypeOfGettingScore>::type>(score);
		m_pSubject->Notify("OnScoreChange", m_CurrentScore);
	}
}

uint64_t Integrian::ScoreComponent::GetCurrentScore() const
{
	return m_CurrentScore;
}

uint64_t Integrian::ScoreComponent::GetMaxScore() const
{
	return m_MaxScore;
}
