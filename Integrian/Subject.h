#pragma once
#ifndef INTEGRIAN_SUBJECT_H
#define INTEGRIAN_SUBJECT_H

#include "pch.h"
#include <vector>
#include "Observer.h"

namespace Integrian
{
	class Observer;
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;
		void AddObserver(Observer* pObserver);
		
		void Notify(const std::string& event)
		{
			for (Observer* pObserver : m_pObservers)
				pObserver->OnNotify(event);
		}

	private:
		std::vector<Observer*> m_pObservers;
	};
}

#endif // !INTEGRIAN_SUBJECT_H