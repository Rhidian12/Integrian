#pragma once
// ====================================
// Author: Rhidian De Wit
// January 2021 ---- Last Edited: January 2021
// ====================================
#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

#include <chrono>
namespace Integrian
{
	class Timer
	{
	public:
		Timer();
		~Timer() = default;

		void Start();

		void Update();
		int GetFPS() const;

		const float GetElapsedSeconds() const;

	private:
		static Timer* m_pInstance;
		const float m_MaxElapsedSeconds;
		float m_ElapsedSeconds;
		float m_TotalElapsedSeconds;
		int m_FPS;
		int m_FPSCounter;
		float m_FPSTimer;
		std::chrono::steady_clock::time_point m_StartTimepoint;
		std::chrono::steady_clock::time_point m_PreviousTimepoint;
	};
}

#endif // !ENGINE_TIMER_H