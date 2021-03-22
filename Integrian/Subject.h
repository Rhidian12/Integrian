#pragma once
#ifndef INTEGRIAN_SUBJECT_H
#define INTEGRIAN_SUBJECT_H

#include "pch.h"
#include <vector>
#include "Observer.h"
#include <algorithm>
#include "Logger.h"

namespace Integrian
{
	class IObserver;
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;

		template<typename ... Args>
		void AddObserver(Observer<Args...>* pObserver)
		{
			ObserverConstIt it{ std::find(m_pObservers.cbegin(),m_pObservers.cend(),pObserver) };
			if (it == m_pObservers.cend())
				m_pObservers.push_back(pObserver);
			else
				Logger::LogError("Observer was already added!\n");
		}

		template<typename ... Args>
		void RemoveObserver(Observer<Args...>* pObserver)
		{
			m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
		}

		template<typename ... Args>
		inline void Notify(const std::string& event, const Args& ... args)
		{
			for (size_t i{}; i < m_pObservers.size(); ++i)
			{
				Observer<Args...>* pTemplatedObserver{ dynamic_cast<Observer<Args...>*>(m_pObservers[i]) };
				if(pTemplatedObserver)
					pTemplatedObserver->OnNotify(event, args...);
			}
		}

	private:
		std::vector<IObserver*> m_pObservers;

		using ObserverConstIt = std::vector<IObserver*>::const_iterator;
	};
}

#endif // !INTEGRIAN_SUBJECT_H