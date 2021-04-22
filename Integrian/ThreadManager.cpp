#include "IntegrianPCH.h" // precompiled header
#include "ThreadManager.h" // header

extern std::atomic<bool> volatile g_IsLooping;

Integrian::ThreadManager::~ThreadManager()
{
	m_CV.notify_all();

	for (std::thread& thread : m_Threads)
		thread.join();

	m_Threads.clear();
}

bool Integrian::ThreadManager::OnEvent(const Event& event)
{
	if (event.GetEvent() == "Change_Application")
	{
		m_CV.notify_all();
		return true;
	}
	else if (event.GetEvent() == "Change_App")
	{
		m_CV.notify_all();
		return true;
	}
	else
		return false;
}

bool Integrian::ThreadManager::AreAllThreadsDone() const
{
	return m_Jobs.empty();
}

Integrian::ThreadManager::ThreadManager()
{
	auto infiniteLoop = [this]()
	{
		while (g_IsLooping.load())
		{
			std::function<void()> pF{};
			{
				std::unique_lock<std::mutex> lock{ m_Mutex };

				m_CV.wait(lock, [this]()
					{
						return (!m_Jobs.empty() || !g_IsLooping.load());
					});

				if (!g_IsLooping.load())
					while (!m_Jobs.empty())
						m_Jobs.pop();

				if (!m_Jobs.empty())
				{
					pF = m_Jobs.front();
					m_Jobs.pop();
				}
			} // make sure the lock goes out of scope

			if (pF)
				pF();
		}
	};

	for (size_t i{}; i < std::thread::hardware_concurrency(); ++i)
		m_Threads.push_back(std::thread{ infiniteLoop });
}