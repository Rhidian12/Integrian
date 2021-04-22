#pragma once

#ifndef INTEGRIAN_EVENTQUEUE_H
#define INTEGRIAN_EVENTQUEUE_H

#include "Event.h" // Event, also includes std::tuple
#include <deque> // std::deque
#include <vector> // std::vector
#include "ListenerInterface.h" // IListener

#include "VisualBenchmark.h" // TODO: REMOVE THIS, ONLY FOR TESTING 

namespace Integrian
{
	class EventQueue final : public IListener
	{
	public:
		virtual ~EventQueue();

		virtual bool OnEvent(const Event& event) override;

		void QueueEvent(Event&& event);
		void Update();

		void AddListener(IListener* pListener);
		void RemoveListener(IListener* pListener);

		/* Returns true if all events have been processed, returns false in other cases */
		[[nodiscard]] bool AreAllEventsProcessed() const;

	private:
		friend struct App_Info;
		EventQueue();

		std::vector<IListener*> m_pListeners{};
		std::deque<Event> m_Events{};
	};
}

#endif // !INTEGRIAN_EVENTQUEUE_H