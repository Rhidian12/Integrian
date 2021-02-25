#pragma once
#ifndef INTEGRIAN_HEALTHCOMPONENT_H
#define INTEGRIAN_HEALTHCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class Observer;
	class TextComponent;
	class HealthComponent : public Component
	{
	public:
		HealthComponent(const uint64_t maxHealth);
		HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth);
		HealthComponent(const uint64_t maxHealth, const uint64_t currentHealth, TextComponent* pTextComponent);

		virtual ~HealthComponent();

		void OnKill();
		Observer* GetObserver() const;

	private:
		uint64_t m_CurrentLives;
		uint64_t m_MaxLives;
		TextComponent* m_pTextComponent;
		Observer* m_pObserver;
	};
}

#endif // !INTEGRIAN_HEALTHCOMPONENT_H