#pragma once

#ifndef INTEGRIAN_EVENTQUEUE_H
#define INTEGRIAN_EVENTQUEUE_H

#include "Event.h" // Event, also includes std::tuple
#include <deque> // std::deque
#include <vector> // std::vector
#include "ListenerInterface.h" // IListener
#include "Singleton.h" // Singleton

#include "VisualBenchmark.h" // TODO: REMOVE THIS, ONLY FOR TESTING 

namespace Integrian
{
	class EventQueue final : public IListener, public Singleton<EventQueue>
	{
	public:
		virtual ~EventQueue();

		virtual bool OnEvent(const Event& event) override;

		void QueueEvent(Event&& event);
		void QueueDelayedEvent(Event&& event, const int nrOfFramesToDelay);
		void Update();

		void AddListener(IListener* pListener);
		void RemoveListener(IListener* pListener);

		/* Returns true if all events have been processed, returns false in other cases */
		[[nodiscard]] bool AreAllEventsProcessed() const;

	private:
		friend class Singleton<EventQueue>;
		EventQueue();

		std::vector<IListener*> m_pListeners{};
		std::deque<Event> m_Events{};
		std::unordered_multimap<int, std::pair<Event, int>> m_DelayedEvents{};

		int m_NumberOfEventsProcessedPerFrame;
	};
}

#endif // !INTEGRIAN_EVENTQUEUE_H