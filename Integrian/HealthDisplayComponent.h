#pragma once
#ifndef INTEGRIAN_HEALTHDISPLAYCOMPONENT_H
#define INTEGRIAN_HEALTHDISPLAYCOMPONENT_H

#include "Component.h"
#include "Observer.h"
#include "Logger.h"

namespace Integrian
{
	class IObserver;
	class TextComponent;
	class HealthComponent;
	class HealthDisplayComponent : public Component
	{
	public:
		HealthDisplayComponent(TextComponent* pTextComponent, const uint64_t startHealth);

		virtual ~HealthDisplayComponent();

		void OnLifeLost(uint64_t currentHealth);
		void OnDeath();

		template<typename ... Args>
		Observer<Args...>* GetObserver() const
		{
			Logger::GetInstance().Log("No Observer of that type was found!", ErrorLevel::error);
			return nullptr;
		}
		template<>
		Observer<uint64_t>* GetObserver() const
		{
			return m_pUint64_tParamObserver;
		}
		template<>
		Observer<>* GetObserver() const
		{
			return m_pNoParamObserver;
		}


	private:
		TextComponent* m_pTextComponent;
		Observer<>* m_pNoParamObserver;
		Observer<uint64_t>* m_pUint64_tParamObserver;
	};
}

#endif // !INTEGRIAN_HEALTHDISPLAYCOMPONENT_H