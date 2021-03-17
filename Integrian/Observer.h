#pragma once
#ifndef INTEGRIAN_OBSERVER_H
#define INTEGRIAN_OBSERVER_H

#include "GameObject.h"
#include <unordered_map>
#include <functional>
#include <vector>

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
			{
				Logger::GetInstance().Log("Event: ", ErrorLevel::error);
				Logger::GetInstance().Log(event, ErrorLevel::error);
				Logger::GetInstance().Log(" was not found!\n", ErrorLevel::error);
			}
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