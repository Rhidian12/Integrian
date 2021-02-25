#include "HealthComponent.h"
#include "Observer.h"

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth)
	: HealthComponent{ maxHealth, maxHealth }
{
	m_pObserver->AddCallback("OnLifeDepleted", this, OnLifeDepleted);
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth)
	: m_CurrentLives{ currentHealth }
	, m_MaxLives{ maxHealth }
	, m_pObserver{ std::make_shared<Observer>() }
{
}

void Integrian::HealthComponent::OnLifeDepleted()
{
	--m_CurrentLives;
}

std::weak_ptr<Integrian::Observer> Integrian::HealthComponent::GetObserver() const
{
	return std::weak_ptr<Observer>(m_pObserver);
}
