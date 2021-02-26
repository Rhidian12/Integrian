#include "HealthDisplayComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "HealthComponent.h"

Integrian::HealthDisplayComponent::HealthDisplayComponent(TextComponent* pTextComponent, HealthComponent* pHealth)
	: m_pObserver{ new Observer{} }
	, m_pTextComponent{ pTextComponent }
	, m_pHealthComponent{ pHealth }
{
	m_pObserver->AddCallback("OnLifeLost", this, &HealthDisplayComponent::OnLifeLost);
	m_pObserver->AddCallback("OnDeath", this, &HealthDisplayComponent::OnDeath);
	m_pTextComponent->SetTextToRender(m_pTextComponent->GetTextToRender() + std::to_string(pHealth->GetCurrentHealth()));
}

Integrian::HealthDisplayComponent::~HealthDisplayComponent()
{
	SAFE_DELETE(m_pObserver);
}

void Integrian::HealthDisplayComponent::OnLifeLost()
{
	std::string currentLives{ m_pTextComponent->GetTextToRender() };
	currentLives.pop_back();
	m_pTextComponent->SetTextToRender(currentLives + std::to_string(m_pHealthComponent->GetCurrentHealth()));
}

void Integrian::HealthDisplayComponent::OnDeath()
{
	m_pTextComponent->SetTextToRender("PlayerDied");
}

Integrian::Observer* Integrian::HealthDisplayComponent::GetObserver() const
{
	return m_pObserver;
}
