#pragma once
#ifndef INTEGRIAN_OBSERVER_H
#define INTEGRIAN_OBSERVER_H

#include "GameObject.h"
#include <unordered_map>
#include <functional>
#include <vector>
#include "Logger.h"

namespace Integrian
{
	class IObserver abstract
	{
	public:
		IObserver() = default;
		virtual ~IObserver() = default;
	};

	template<typename ... Args>
	class Observer final : public IObserver
	{
	public:
		Observer() = default;
		~Observer() = default;

		void OnNotify(const std::string& event, Args ... args)
		{
			auto iterator{ m_pFunctions.find(event) };
			if (iterator != m_pFunctions.cend())
				for (const std::function<void(Args ...)>& pFunction : iterator->second)
					pFunction(args...);
			else
				Logger::LogError("Event: " + event + " was not found!\n");
		}

		template<typename Type>
		void AddCallback(const std::string& event, Type* pObject, void(Type::* pFunction)(Args ...))
		{
			m_pFunctions[event].push_back([=](Args ... args)
				{
					return (pObject->*pFunction)(args...);
				});
		}

	private:
		std::unordered_map<std::string, std::vector<std::function<void(Args ...)>>> m_pFunctions;
	};
}

#endif // !INTEGRIAN_OBSERVER_H