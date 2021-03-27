#pragma once

#ifndef INTEGRIAN_EVENTQUEUE_H
#define INTEGRIAN_EVENTQUEUE_H

#include "Singleton.h" // Singleton
#include "Event.h" // IEvent and Event
#include <queue> // std::queue
#include <vector> // std::vector
#include "ListenerInterface.h" // Integrian::IListener
#include <mutex> // std::mutex, std::unique_lock, std::condition_variable

#include "VisualBenchmark.h" // TODO: REMOVE THIS, ONLY FOR TESTING 

namespace Integrian
{
	class EventQueue final : public Singleton<EventQueue>
	{
	public:
		EventQueue() = default;
		virtual ~EventQueue();

		inline void QueueEvent(Event&& event)
		{
			{
				std::unique_lock<std::mutex> lock{ m_Mutex };
				m_Events.push(std::forward<Event>(event)); // we need to std::forward this so that it actually moves this instead of copying like a little fucking bitch
			} // make sure the lock goes out of scope before notifying a thread

			m_CV.notify_one();
		}

		inline void AddListener(IListener* pListener)
		{
			m_pListeners.push_back(pListener);
		}

		inline void Update()
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };
			//TIME();

			m_CV.wait(lock, [this]()
				{
					return !m_Events.empty();
				});

			bool wasEventProcessed{};
			for (IListener* pListener : m_pListeners)
				if (pListener->OnEvent(m_Events.front()))
					wasEventProcessed = true;

			if (wasEventProcessed)
			{
				m_EventsToBeDeleted.push_back(std::move(m_Events.front()));
				m_Events.pop();
			}
		}

	private:
		friend class Singleton<EventQueue>;

		std::vector<IListener*> m_pListeners{};
		std::queue<Event> m_Events{};
		std::vector<Event> m_EventsToBeDeleted{};

		std::mutex m_Mutex{};
		std::condition_variable m_CV{};
	};
}

#endif // !INTEGRIAN_EVENTQUEUE_H