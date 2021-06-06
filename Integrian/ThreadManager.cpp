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

bool Integrian::ThreadManager::AreAllThreadsDone() const noexcept
{
	for (const bool isJobDone : m_AreJobsDone)
		if (!isJobDone)
			return false;

	return true;
}

const std::queue<std::function<void()>>& Integrian::ThreadManager::GetJobs() const noexcept
{
	return m_Jobs;
}

void Integrian::ThreadManager::InfiniteLoop(const uint32_t index)
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
				m_AreJobsDone[index] = false;
				pF = m_Jobs.front();
				m_Jobs.pop();
			}
		} // make sure the lock goes out of scope

		if (pF)
			pF();

		{
			std::unique_lock<std::mutex> lock{ m_Mutex }; // re acquire the lock to set the job to be done
			m_AreJobsDone[index] = true;
		}
	}
}

Integrian::ThreadManager::ThreadManager()
{
	//auto infiniteLoop = [this]()
	//{
	//	while (g_IsLooping.load())
	//	{
	//		std::function<void()> pF{};
	//		{
	//			std::unique_lock<std::mutex> lock{ m_Mutex };

	//			m_CV.wait(lock, [this]()
	//				{
	//					return (!m_Jobs.empty() || !g_IsLooping.load());
	//				});

	//			if (!g_IsLooping.load())
	//				while (!m_Jobs.empty())
	//					m_Jobs.pop();

	//			if (!m_Jobs.empty())
	//			{
	//				pF = m_Jobs.front();
	//				m_Jobs.pop();
	//			}
	//		} // make sure the lock goes out of scope

	//		if (pF)
	//			pF();
	//	}
	//};

	for (size_t i{}; i < std::thread::hardware_concurrency(); ++i)
	{
		//m_Threads.push_back(std::thread{ infiniteLoop });
		m_Threads.push_back(std::thread{ std::bind(&ThreadManager::InfiniteLoop, this, uint32_t(i)) });
		m_AreJobsDone.push_back(true);
	}
}