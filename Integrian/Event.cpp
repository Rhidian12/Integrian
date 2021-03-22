#include "pch.h"
#include "Event.h"

Integrian::Event::Event(const Event& other) noexcept
{
	m_Event = other.m_Event;
	m_pData = other.m_pData;
}
Integrian::Event::Event(Event&& other) noexcept
{
	m_Event = other.m_Event;
	m_pData = other.m_pData;

	other.m_pData = nullptr;
}

Integrian::Event::~Event()
{
	SafeDelete(m_pData);
}

const Integrian::Events Integrian::Event::GetEvent() const
{
	return m_Event;
}