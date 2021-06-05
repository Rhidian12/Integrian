#include "IntegrianPCH.h" // precompiled header
#include "EventQueue.h" // header
#include <algorithm> // std::remove_if
#include "Logger.h" // Logger

Integrian::EventQueue::EventQueue()
	: m_NumberOfEventsProcessedPerFrame{ 5 }
{
	AddListener(this);
}

Integrian::EventQueue::~EventQueue()
{
	m_Events.clear();
	m_DelayedEvents.clear();
	m_pListeners.clear();
}

bool Integrian::EventQueue::OnEvent(const Event& event)
{
	const std::string eventName{ event.GetEvent() };

	return false;
}

void Integrian::EventQueue::QueueEvent(Event&& event)
{
	m_Events.push_back(std::forward<Event>(event)); // we need to std::forward this so that it actually moves this instead of copying like a little fucking bitch
}

void Integrian::EventQueue::QueueDelayedEvent(Event&& event, const int nrOfFramesToDelay)
{
	assert(nrOfFramesToDelay != 0);
	m_DelayedEvents.insert(std::make_pair(nrOfFramesToDelay, std::make_pair(std::forward<Event>(event), 0)));
}

void Integrian::EventQueue::Update()
{
	//TIME();

	if (!m_Events.empty())
	{
		for (int i{}; i < m_NumberOfEventsProcessedPerFrame; ++i)
		{
			bool wasEventProcessed{};
			for (IListener* pListener : m_pListeners)
				if (pListener->OnEvent(m_Events.front()))
					wasEventProcessed = true;

			if (wasEventProcessed)
				m_Events.pop_front();
			else // Requeue event by pushing it to the back
			{
				Event tempEvent{ std::remove_reference_t<Event>(m_Events.front()) }; // make sure it copies the Event, and it doesn't reference it
				m_Events.push_back(tempEvent);
				m_Events.pop_front();
			}

			if (m_Events.empty())
				break;
		}
	}

	// Update delayed events
	for (std::pair<const int, std::pair<Event, int>>& pair : m_DelayedEvents)
	{
		if (pair.first == ++pair.second.second)
		{
			m_Events.push_back(std::remove_reference_t<Event>(pair.second.first)); // make sure we copy the event
		}
	}

	// remove delayed events which are done
	Erase_If(m_DelayedEvents, [](const std::pair<const int, std::pair<Event, int>>& pair)->bool
		{
			return pair.first == pair.second.second;
		});
}

void Integrian::EventQueue::AddListener(IListener* pListener)
{
	std::vector<IListener*>::const_iterator cIt{ std::find_if(m_pListeners.begin(), m_pListeners.end(), [pListener](IListener* pL)->bool
		{
			return pListener == pL;
		}) };

	if (cIt == m_pListeners.cend())
		m_pListeners.push_back(pListener);
	else
		Logger::LogError("Cannot add the same listener twice to the EventQueue!\n");
}

void Integrian::EventQueue::RemoveListener(IListener* pListener)
{
	std::vector<IListener*>::iterator it{ std::remove_if(m_pListeners.begin(), m_pListeners.end(),[pListener](IListener* pL)->bool
		{
			return pListener == pL;
		})
	};

	m_pListeners.erase(it, m_pListeners.end());
}

bool Integrian::EventQueue::AreAllEventsProcessed() const
{
	return m_Events.empty();
}
