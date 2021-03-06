#pragma once
#ifndef INTEGRIAN_SCORECOMPONENT_H
#define INTEGRIAN_SCORECOMPONENT_H

#include "Component.h"
#include <limits>
#include <memory>
#include "Observer.h"
#include "Subject.h"

enum class TypeOfGettingScore : uint64_t
{
	ColourChange = 25,
	CoilyDefeated = 500,
	RemainingDiscs = 50,
	CatchingSlickAndSam = 300
};

namespace Integrian
{
	class ScoreComponent final : public Component
	{
	public:
		ScoreComponent(const uint64_t maxScore = std::numeric_limits<uint64_t>::max() , const uint64_t currentScore = 0);
		virtual ~ScoreComponent() = default;

		template<typename ... Args>
		void AddObserver(Observer<Args...>* pObserver)
		{
			m_pSubject->AddObserver(pObserver);
		}

		void ChangeScore(const TypeOfGettingScore score);

		[[nodiscard]] uint64_t GetCurrentScore() const;
		[[nodiscard]] uint64_t GetMaxScore() const;

	private:
		uint64_t m_CurrentScore;
		uint64_t m_MaxScore;
		std::unique_ptr<Subject> m_pSubject;
	};
}

#endif // !INTEGRIAN_SCORECOMPONENT_H