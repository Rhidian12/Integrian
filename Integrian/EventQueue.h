#pragma once

#ifndef INTEGRIAN_EVENTQUEUE_H
#define INTEGRIAN_EVENTQUEUE_H

#include "Singleton.h" // Singleton
#include "Event.h" // Event, also includes std::tuple
#include <deque> // std::deque
#include <vector> // std::vector
#include "ListenerInterface.h" // IListener
#include <mutex> // std::mutex, std::unique_lock, std::condition_variable

#include "VisualBenchmark.h" // TODO: REMOVE THIS, ONLY FOR TESTING 

namespace Integrian
{
	class EventQueue final : public Singleton<EventQueue>, public IListener
	{
	public:
		EventQueue();
		virtual ~EventQueue();

		virtual bool OnEvent(const Event& event) override;

		void QueueEvent(Event&& event);
		void Update();

		void AddListener(IListener* pListener);
		void RemoveListener(IListener* pListener);

	private:
		friend class Singleton<EventQueue>;

		std::vector<IListener*> m_pListeners{};
		std::deque<Event> m_Events{};

		std::mutex m_Mutex{};
		std::condition_variable m_CV{};
	};
}

#endif // !INTEGRIAN_EVENTQUEUE_H