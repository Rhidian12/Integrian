#pragma once
#ifndef INTEGRIAN_HEALTHCOMPONENT_H
#define INTEGRIAN_HEALTHCOMPONENT_H

#include "Component.h"
#include <memory>

namespace Integrian
{
	class Observer;
	class Subject;
	class HealthComponent final : public Component
	{
	public:
		HealthComponent(const uint64_t maxLives);
		HealthComponent(const uint64_t maxLives, const uint64_t currentLives);
		virtual ~HealthComponent() = default;

		void AddObserver(Observer* pObserver);
		void DecreaseLivesByValue(const uint64_t value);

		[[nodiscard]] uint64_t GetCurrentHealth() const;
		[[nodiscard]] uint64_t GetMaxHealth() const;

	private:
		uint64_t m_MaxLives;
		uint64_t m_CurrentLives;
		std::unique_ptr<Subject> m_pSubject;
	};
}

#endif // !INTEGRIAN_HEALTHCOMPONENT_H