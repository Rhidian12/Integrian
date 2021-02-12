#include "pch.h"
#include "Timer.h"

extern bool g_IsUpdateFixed;
extern float g_TimePerFrame;

Integrian::Timer::Timer()
	: m_MaxElapsedSeconds{ 0.1f }
	, m_ElapsedSeconds{}
	, m_TotalElapsedSeconds{}
	, m_FPS{}
	, m_FPSCounter{}
	, m_FPSTimer{}
	, m_StartTimepoint{}
	, m_PreviousTimepoint{}
{
	Start();
}

void Integrian::Timer::Start()
{
	//m_CurrentTimepoint = std::chrono::steady_clock::now();
	m_PreviousTimepoint = std::chrono::steady_clock::now();
}

void Integrian::Timer::Update()
{
	m_StartTimepoint = std::chrono::steady_clock::now();
	m_ElapsedSeconds = std::chrono::duration<float>(m_StartTimepoint - m_PreviousTimepoint).count();
	m_PreviousTimepoint = m_StartTimepoint;

	++m_FPSCounter;
	m_FPSTimer += m_ElapsedSeconds;
	if (m_FPSTimer >= 1.f)
	{
		m_FPS = m_FPSCounter;
		m_FPSCounter = 0;
		m_FPSTimer = 0.f;
	}
}

int Integrian::Timer::GetFPS() const
{
	return m_FPS;
}

const float Integrian::Timer::GetElapsedSeconds() const
{
	return m_ElapsedSeconds;
}
