#include "pch.h"
#include "Timer.h"

Integrian::Timer::Timer()
	: m_MaxElapsedSeconds{ 0.1f }
	, m_ElapsedSeconds{}
	, m_TotalElapsedSeconds{}
	, m_FPS{}
	, m_FPSCounter{}
	, m_FPSTimer{}
	, m_TimePerFrame{ 1.f / 144.f }
{
	Start();
}

void Integrian::Timer::Start()
{
	m_PreviousTimepoint = std::chrono::steady_clock::now();
}

void Integrian::Timer::Update()
{
	m_StartTimepoint = std::chrono::steady_clock::now();
	m_ElapsedSeconds = std::chrono::duration<float>(m_StartTimepoint - m_PreviousTimepoint).count();
	m_ElapsedSeconds = std::min(m_ElapsedSeconds, m_MaxElapsedSeconds);
	m_TotalElapsedSeconds += m_ElapsedSeconds;
	
	m_PreviousTimepoint = m_StartTimepoint;

	m_FPS = int(1.f / m_ElapsedSeconds);
}

int Integrian::Timer::GetFPS() const
{
	return m_FPS;
}

float Integrian::Timer::GetElapsedSeconds() const
{
	return m_ElapsedSeconds;
}

float Integrian::Timer::GetTimePerFrame() const
{
	return m_TimePerFrame;
}

float Integrian::Timer::GetTotalElapsedSeconds() const
{
	return m_TotalElapsedSeconds;
}
