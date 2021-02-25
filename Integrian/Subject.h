#pragma once
#ifndef INTEGRIAN_SUBJECT_H
#define INTEGRIAN_SUBJECT_H

#include "pch.h"
#include <vector>
#include <memory>
#include "Observer.h"

namespace Integrian
{
	class Observer;
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;
		void AddObserver(std::weak_ptr<Observer> pObserver);
		
		void Notify(const std::string& event)
		{
			for (std::weak_ptr<Observer> pObserver : m_pObservers)
				pObserver.lock()->OnNotify(event);
		}

	private:
		std::vector<std::weak_ptr<Observer>> m_pObservers;
	};
}

#endif // !INTEGRIAN_SUBJECT_H