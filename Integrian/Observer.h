#pragma once
#ifndef INTEGRIAN_OBSERVER_H
#define INTEGRIAN_OBSERVER_H

#include "GameObject.h"
#include <unordered_map>
#include <functional>
#include <vector>

namespace Integrian
{
	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		void OnNotify(const std::string& event);

		template<typename Type>
		void AddCallback(const std::string& event, Type* pObject, void(Type::* pFunction)())
		{
			m_pFunctions[event].push_back(std::bind(pFunction, pObject));
		}

	private:
		std::unordered_map<std::string, std::vector<std::function<void()>>> m_pFunctions;

		using EventFunctionPair = std::pair<std::string, std::vector<std::function<void()>>>;
		using EventFunctionConstIt = std::unordered_map<std::string, std::vector<std::function<void()>>>::const_iterator;
	};
}

#endif // !INTEGRIAN_OBSERVER_H