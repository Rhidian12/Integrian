#pragma once
#ifndef INTEGRIAN_SCOREDISPLAYCOMPONENT_H
#define INTEGRIAN_SCOREDISPLAYCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class Observer;
	class TextComponent;
	class ScoreComponent;
	class ScoreDisplayComponent final : public Component
	{
	public:
		ScoreDisplayComponent(TextComponent* pTextComponent, ScoreComponent* pScoreComponent);
		virtual ~ScoreDisplayComponent();

		void OnScoreChange();

		[[nodiscard]] Observer* GetObserver() const;

	private:
		TextComponent* m_pTextComponent;
		ScoreComponent* m_pScoreComponent;
		Observer* m_pObserver;
	};
}

#endif // !INTEGRIAN_SCOREDISPLAYCOMPONENT_H