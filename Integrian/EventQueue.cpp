#include "EventQueue.h" // header
#include <algorithm> // std::remove_if
#include "Logger.h" // Logger

Integrian::EventQueue::EventQueue()
{
	AddListener(this);
}

Integrian::EventQueue::~EventQueue()
{
	m_Events.clear();
	m_pListeners.clear();
}

bool Integrian::EventQueue::OnEvent(const Event& event)
{
	const std::string eventName{ event.GetEvent() };

	if (eventName == "EndOfFrame") // let's see what to do with this
	{
		return true;
	}
	else
		return false;
}

void Integrian::EventQueue::QueueEvent(Event&& event)
{
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };
		m_Events.push_back(std::forward<Event>(event)); // we need to std::forward this so that it actually moves this instead of copying like a little fucking bitch
	} // make sure the lock goes out of scope before notifying a thread

	m_CV.notify_one();
}

void Integrian::EventQueue::Update()
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
		m_Events.pop_front();
	else // Requeue event by pushing it to the back
	{
		Event tempEvent{ std::remove_reference_t<Event>(m_Events.front()) }; // make sure it copies the Event, and it doesn't reference it
		m_Events.push_back(tempEvent);
		m_Events.pop_front();
	}
}

void Integrian::EventQueue::AddListener(IListener* pListener)
{
	m_pListeners.push_back(pListener);
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
