#include "pch.h"
#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "Observer.h"
#include "ScoreComponent.h"

Integrian::ScoreDisplayComponent::ScoreDisplayComponent(TextComponent* pTextComponent, ScoreComponent* pScoreComponent)
	: m_pTextComponent{ pTextComponent }
	, m_pScoreComponent{ pScoreComponent }
	, m_pObserver{ new Observer{} }
{
	m_pTextComponent->SetTextToRender(pTextComponent->GetTextToRender() + std::to_string(pScoreComponent->GetCurrentScore()));
	m_pObserver->AddCallback("OnScoreChange", this, &ScoreDisplayComponent::OnScoreChange);
}

Integrian::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	SAFE_DELETE(m_pObserver);
}

void Integrian::ScoreDisplayComponent::OnScoreChange()
{
	std::string currentText{ m_pTextComponent->GetTextToRender() };
	currentText.erase(currentText.find_last_of(" ") + 1, currentText.size() - currentText.find_last_of(" "));
	m_pTextComponent->SetTextToRender(currentText + std::to_string(m_pScoreComponent->GetCurrentScore()));
}

Integrian::Observer* Integrian::ScoreDisplayComponent::GetObserver() const
{
	return m_pObserver;
}
