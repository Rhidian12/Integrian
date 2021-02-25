#include "HealthComponent.h"
#include "Observer.h"

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth)
	: HealthComponent{ maxHealth, maxHealth }
{
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth)
	: m_CurrentLives{ currentHealth }
	, m_MaxLives{ maxHealth }
	, m_pObserver{ std::make_shared<Observer>() }
{
	m_pObserver->AddCallback("Kill", this, &HealthComponent::OnKill);
}

void Integrian::HealthComponent::OnKill()
{
	if(m_CurrentLives > 0)
		--m_CurrentLives;
	else
	{
		ImGui::
	}
}

std::weak_ptr<Integrian::Observer> Integrian::HealthComponent::GetObserver() const
{
	return std::weak_ptr<Observer>(m_pObserver);
}
