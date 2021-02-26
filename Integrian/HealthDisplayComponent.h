#pragma once
#ifndef INTEGRIAN_HEALTHDISPLAYCOMPONENT_H
#define INTEGRIAN_HEALTHDISPLAYCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class Observer;
	class TextComponent;
	class HealthComponent;
	class HealthDisplayComponent : public Component
	{
	public:
		HealthDisplayComponent(TextComponent* pTextComponent, HealthComponent* pHealth);

		virtual ~HealthDisplayComponent();

		void OnLifeLost();
		void OnDeath();

		Observer* GetObserver() const;

	private:
		TextComponent* m_pTextComponent;
		HealthComponent* m_pHealthComponent;
		Observer* m_pObserver;
	};
}

#endif // !INTEGRIAN_HEALTHDISPLAYCOMPONENT_H