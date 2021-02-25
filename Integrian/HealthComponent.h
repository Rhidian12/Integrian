#pragma once
#ifndef INTEGRIAN_HEALTHCOMPONENT_H
#define INTEGRIAN_HEALTHCOMPONENT_H

#include "Component.h"
#include <memory>

namespace Integrian
{
	class Observer;
	class HealthComponent : public Component
	{
	public:
		HealthComponent(const uint64_t maxHealth);
		HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth);

		void OnKill();
		std::weak_ptr<Observer> GetObserver() const;

	private:
		uint64_t m_CurrentLives;
		uint64_t m_MaxLives;
		std::shared_ptr<Observer> m_pObserver;
	};
}

#endif // !INTEGRIAN_HEALTHCOMPONENT_H