#pragma once
#ifndef INTEGRIAN_SCOREDISPLAYCOMPONENT_H
#define INTEGRIAN_SCOREDISPLAYCOMPONENT_H

#include "Component.h"
#include "Observer.h"

namespace Integrian
{
	class TextComponent;
	class ScoreComponent;
	class ScoreDisplayComponent final : public Component
	{
	public:
		ScoreDisplayComponent(TextComponent* pTextComponent, uint64_t currentScore);
		virtual ~ScoreDisplayComponent();

		void OnScoreChange(uint64_t currentScore);

		[[nodiscard]] Observer<uint64_t>* GetObserver() const
		{
			return m_pObserver;
		}

	private:
		TextComponent* m_pTextComponent;
		Observer<uint64_t>* m_pObserver;
	};
}

#endif // !INTEGRIAN_SCOREDISPLAYCOMPONENT_H