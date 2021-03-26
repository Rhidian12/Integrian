#include "ThreadManager.h" // header

extern bool g_IsLooping;

Integrian::ThreadManager::~ThreadManager()
{
	m_CV.notify_all();

	for (std::thread& thread : m_Threads)
		thread.join();

	m_Threads.clear();
}

Integrian::ThreadManager::ThreadManager()
{
	auto infiniteLoop = [this]()
	{
		while (g_IsLooping)
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };

			m_CV.wait(lock, [this]()
				{
					return (!m_Jobs.empty() || !g_IsLooping);
				});

			if (!m_Jobs.empty())
			{
				auto pF = m_Jobs.front();
				m_Jobs.pop();

				pF();
			}
		}
	};

	for (size_t i{}; i < std::thread::hardware_concurrency(); ++i)
		m_Threads.push_back(std::thread{ infiniteLoop });
}