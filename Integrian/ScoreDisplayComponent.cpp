#include "IntegrianPCH.h"
#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "Observer.h"
#include "ScoreComponent.h"

Integrian::ScoreDisplayComponent::ScoreDisplayComponent(TextComponent* pTextComponent, uint64_t currentScore)
	: m_pTextComponent{ pTextComponent }
	, m_pObserver{ new Observer<uint64_t>{} }
{
	m_pTextComponent->SetTextToRender(pTextComponent->GetTextToRender() + std::to_string(currentScore));
	m_pObserver->AddCallback("OnScoreChange", this, &ScoreDisplayComponent::OnScoreChange);
}

Integrian::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	SafeDelete(m_pObserver);
}

void Integrian::ScoreDisplayComponent::OnScoreChange(uint64_t currentScore)
{
	std::string currentText{ m_pTextComponent->GetTextToRender() };
	currentText.erase(currentText.find_last_of(" ") + 1, currentText.size() - currentText.find_last_of(" "));
	m_pTextComponent->SetTextToRender(currentText + std::to_string(currentScore));
}
