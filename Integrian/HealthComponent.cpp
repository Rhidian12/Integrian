#include "HealthComponent.h"
#include "Observer.h"
#include "TextComponent.h"

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth)
	: HealthComponent{ maxHealth, maxHealth }
{
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth)
	: HealthComponent{ maxHealth,currentHealth,nullptr }
{
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth, TextComponent* pTextComponent)
	: m_CurrentLives{ currentHealth }
	, m_MaxLives{ maxHealth }
	, m_pObserver{ new Observer{} }
	, m_pTextComponent{ pTextComponent }
{
	m_pObserver->AddCallback("Kill", this, &HealthComponent::OnKill);
	m_pTextComponent->SetTextToRender(std::to_string(m_CurrentLives));
}

Integrian::HealthComponent::~HealthComponent()
{
	SAFE_DELETE(m_pObserver);
}

void Integrian::HealthComponent::OnKill()
{
	if (m_CurrentLives > 0)
	{
		std::cout << "Lost a life" << std::endl;
		--m_CurrentLives;
	}
	m_pTextComponent->SetTextToRender(std::to_string(m_CurrentLives));
}

Integrian::Observer* Integrian::HealthComponent::GetObserver() const
{
	return m_pObserver;
}
