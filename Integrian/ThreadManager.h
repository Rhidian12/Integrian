#pragma once

#ifndef INTEGRIAN_THREADMANAGER_H
#define INTEGRIAN_THREADMANAGER_H

#include "Singleton.h" // Singleton
#include <thread> // std::thread
#include <vector> // std::vector
#include "Logger.h" // Logger
#include <mutex> // std::mutex, std::lock_guard
#include <queue> // std::queue
#include <functional> // std::function

// Reference: https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

namespace Integrian
{
	class ThreadManager final : public Singleton<ThreadManager>
	{
	public:
		virtual ~ThreadManager();

		/*
		All threads get closed automatically at the end of the program, this, of course, will not work when they are made with a while(true) loop
		*/
		template<typename Lambda>
		void GetThread(Lambda&& lambda)
		{
			std::unique_lock<std::mutex> lock{ m_Mutex };
			m_Jobs.push(lambda);
			m_CV.notify_one();
		}

	private:
		friend class Singleton<ThreadManager>;

		ThreadManager();

		std::vector<std::thread> m_Threads{};
		std::queue<std::function<void()>> m_Jobs{};
		std::mutex m_Mutex{};
		std::condition_variable m_CV{};
	};
}

#endif // !INTEGRIAN_THREADMANAGER_H