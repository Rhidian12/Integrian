#include "pch.h"
#include "EventQueue.h"

Integrian::EventQueue::~EventQueue()
{
	while (!m_Events.empty())
		m_Events.pop();

	m_EventsToBeDeleted.clear();
	m_pListeners.clear();
}
