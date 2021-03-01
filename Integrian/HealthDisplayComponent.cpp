#include "HealthDisplayComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "HealthComponent.h"

Integrian::HealthDisplayComponent::HealthDisplayComponent(TextComponent* pTextComponent, const uint64_t startHealth)
	: m_pNoParamObserver{ new Observer<>{} }
	, m_pUint64_tParamObserver{ new Observer<uint64_t>{} }
	, m_pTextComponent{ pTextComponent }
{
	m_pUint64_tParamObserver->AddCallback("OnLifeLost", this, &HealthDisplayComponent::OnLifeLost);
	m_pNoParamObserver->AddCallback("OnDeath", this, &HealthDisplayComponent::OnDeath);
	m_pTextComponent->SetTextToRender(m_pTextComponent->GetTextToRender() + std::to_string(startHealth));
}

Integrian::HealthDisplayComponent::~HealthDisplayComponent()
{
	SafeDelete(m_pNoParamObserver);
	SafeDelete(m_pUint64_tParamObserver);
}

void Integrian::HealthDisplayComponent::OnLifeLost(uint64_t currentHealth)
{
	std::string currentLives{ m_pTextComponent->GetTextToRender() };
	currentLives.pop_back();
	m_pTextComponent->SetTextToRender(currentLives + std::to_string(currentHealth));
}

void Integrian::HealthDisplayComponent::OnDeath()
{
	m_pTextComponent->SetTextToRender("PlayerDied");
}
