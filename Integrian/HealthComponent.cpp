#include "pch.h"
#include "HealthComponent.h"
#include "Observer.h"
#include "Subject.h"
#include "ServiceLocator.h"
#include "EventQueue.h"

Integrian::HealthComponent::HealthComponent(const uint64_t maxLives)
	: HealthComponent{ maxLives,maxLives }
{
}

Integrian::HealthComponent::HealthComponent(const uint64_t maxLives, const uint64_t currentLives)
	: m_MaxLives{ maxLives }
	, m_CurrentLives{ currentLives }
	, m_pSubject{ std::make_unique<Subject>() }
{
	ServiceLocator::Provide(new AudioPlayerLogged{}); // TODO: MOVE THIS TO TEST_APP
	AudioPlayerLogged* pAudio{ ServiceLocator::GetService<AudioPlayerLogged>() };
	pAudio->AddSound(0, "Data/menu3.wav");
}

void Integrian::HealthComponent::DecreaseLivesByValue(const uint64_t value)
{
	if (m_CurrentLives > 0)
	{
		m_CurrentLives -= value;

		if (m_CurrentLives <= 0)
			m_pSubject->Notify("OnDeath");
		else
			m_pSubject->Notify("OnLifeLost", m_CurrentLives);

		EventQueue::GetInstance().QueueEvent(Event{ Events::PlaySound, 0, false, 0, 100 });
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
