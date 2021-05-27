#pragma once
#ifndef INTEGRIAN_OBSERVER_H
#define INTEGRIAN_OBSERVER_H

#include "GameObject.h" // GameObject
#include <unordered_map> // std::unordered_map
#include <functional> // std::function 
#include <vector> // std::vector

namespace Integrian
{
	class Observer // this is supposed to be inherited from
	{
		using UMapCIt = std::unordered_map<std::string, std::vector<std::function<void()>>>::const_iterator;
	public:
		Observer() = default;

		virtual void OnNotify(const std::string& event) = 0;

		//void OnNotify(const std::string& event)
		//{
		//	const UMapCIt cIt{ m_pFunctions.find(event) };
		//
		//	if (cIt != m_pFunctions.cend())
		//		for (const std::function<void()>& pFunction : cIt->second)
		//			pFunction();
		//}

		//void AddCallback(const std::string& event, std::function<void()>&& pFunction)
		//{
		//	m_pFunctions[event].push_back(pFunction);
		//}

	private:
		//std::unordered_map<std::string, std::vector<std::function<void()>>> m_pFunctions;
	};

	//class IObserver abstract
	//{
	//public:
	//	IObserver() = default;
	//	virtual ~IObserver() = default;
	//};

	//template<typename ... Args>
	//class Observer final : public IObserver // TODO: Make this an interface
	//{
	//public:
	//	Observer() = default;
	//	~Observer() = default;

	//	void OnNotify(const std::string& event, Args ... args)
	//	{
	//		auto iterator{ m_pFunctions.find(event) };
	//		if (iterator != m_pFunctions.cend())
	//			for (const std::function<void(Args ...)>& pFunction : iterator->second)
	//				pFunction(args...);
	//		else
	//			Logger::LogError("Event: " + event + " was not found!\n");
	//	}

	//	template<typename Type>
	//	void AddCallback(const std::string& event, Type* pObject, void(Type::* pFunction)(Args ...))
	//	{
	//		m_pFunctions[event].push_back([=](Args ... args)
	//			{
	//				return (pObject->*pFunction)(args...);
	//			});
	//	}

	//private:
	//	std::unordered_map<std::string, std::vector<std::function<void(Args ...)>>> m_pFunctions;
	//};
}

#endif // !INTEGRIAN_OBSERVER_H