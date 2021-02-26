#include "pch.h"
#include "HealthComponent.h"
#include "Observer.h"
#include "Subject.h"

Integrian::HealthComponent::HealthComponent(const uint64_t maxLives)
	: HealthComponent{ maxLives,maxLives }
{
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxLives, const uint64_t currentLives)
	: m_MaxLives{ maxLives }
	, m_CurrentLives{ currentLives }
	, m_pSubject{ std::make_unique<Subject>() }
{
}

void Integrian::HealthComponent::AddObserver(Observer* pObserver)
{
	m_pSubject->AddObserver(pObserver);
}

void Integrian::HealthComponent::DecreaseLivesByValue(const uint64_t value)
{
	if (m_CurrentLives > 0)
	{
		m_CurrentLives -= value;

		if (m_CurrentLives == 0)
			m_pSubject->Notify("OnDeath");
		else
			m_pSubject->Notify("OnLifeLost");
	}

}

uint64_t Integrian::HealthComponent::GetCurrentHealth() const
{
	return m_CurrentLives;
}

uint64_t Integrian::HealthComponent::GetMaxHealth() const
{
	return m_MaxLives;
}
