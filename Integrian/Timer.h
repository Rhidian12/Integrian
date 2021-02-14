#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021 ---- Last Edited: January 2021
// ====================================
#ifndef INTEGRIAN_TIMER_H
#define INTEGRIAN_TIMER_H

#include "Singleton.h"
#include <chrono>

namespace Integrian
{
	class Timer final : public Singleton<Timer>
	{
	public:
		~Timer() = default;

		void Start();

		void Update();

		[[nodiscard]] int GetFPS() const;
		[[nodiscard]] float GetElapsedSeconds() const;
		[[nodiscard]] float GetTimePerFrame() const;
		[[nodiscard]] float GetTotalElapsedSeconds() const;
	
	private:
		Timer();
		friend class Singleton<Timer>;
		
		const float m_MaxElapsedSeconds;
		float m_ElapsedSeconds;
		float m_TotalElapsedSeconds;
		int m_FPS;
		int m_FPSCounter;
		float m_FPSTimer;
		float m_TimePerFrame;

		std::chrono::steady_clock::time_point m_StartTimepoint;
		std::chrono::steady_clock::time_point m_PreviousTimepoint;
	};
}

#endif // !INTEGRIAN_TIMER_H