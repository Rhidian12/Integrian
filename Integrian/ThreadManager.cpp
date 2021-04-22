#include "ThreadManager.h" // header

extern std::atomic<bool> g_IsLooping;

Integrian::ThreadManager::~ThreadManager()
{
	std::cout << "FILLER" << std::endl;
	std::cout << "FILLER" << std::endl;
	std::cout << "FILLER" << std::endl;
	std::cout << "FILLER" << std::endl;
	std::cout << "FILLER" << std::endl;
	
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
		m_A.store(m_A.load() + 1);
		std::cout << m_A.load() << " threads went out of scope" << std::endl;

		std::cout << "Thread with thread ID: " << std::this_thread::get_id() << std::endl;
	};

	for (size_t i{}; i < std::thread::hardware_concurrency(); ++i)
		m_Threads.push_back(std::thread{ infiniteLoop });
}