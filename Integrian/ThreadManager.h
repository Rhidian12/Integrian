#pragma once

#ifndef INTEGRIAN_THREADMANAGER_H
#define INTEGRIAN_THREADMANAGER_H

#include "pch.h" // AlwaysFalse()
#include "Singleton.h" // Singleton
#include <thread> // std::thread
#include <vector> // std::vector
#include "Logger.h" // Logger
#include <mutex> // std::mutex, std::unique_lock
#include <queue> // std::queue
#include <functional> // std::function
#include <type_traits> // std::is_assignable_v

// Reference: https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

namespace Integrian
{
	class ThreadManager final : public Singleton<ThreadManager>
	{
	public:
		virtual ~ThreadManager();

		/*
		All threads get closed automatically at the end of the program, this, of course, will not work when they are made with a while(true) loop

		Make sure that all data passed to the lambda's capture group is passed by VALUE, not by reference! Things might go out of scope and thus become not thread-safe.

		This function merely assigns threads to lambdas given to it, this in itself is done in a threadsafe way, however the data inside must still be handled thread safely!

		Use this function at your own risk!
		*/
		template<typename Lambda> // this could be std::function<void()>, but the compiler can deduce this itself, plus this makes it easier to read through intellisense and reading the function
		void AssignThread(Lambda&& lambda)
		{
			if constexpr (std::is_assignable_v<std::function<void()>, Lambda>) // Can Lambda be assigned to std::function<void()>
			{
				std::unique_lock<std::mutex> lock{ m_Mutex };
				m_Jobs.push(lambda);
				m_CV.notify_one();
			}
			else
				static_assert(AlwaysFalse(), "The function assigned to AssignThread() was not a lambda");
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