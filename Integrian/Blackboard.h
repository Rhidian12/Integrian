#pragma once

#ifndef INTEGRIAN_BLACKBOARD_H
#define INTEGRIAN_BLACKBOARD_H

#include "IntegrianPCH.h"
#include <tuple> // std::tuple
#include <unordered_map> // std::unordered_map
#include <memory> // std::shared_ptr

namespace Integrian
{
	class IBlackboardData
	{
	public:
		virtual ~IBlackboardData() = default;
	};

	template<typename ... Args>
	class BlackboardData final : public IBlackboardData
	{
	public:
		BlackboardData(const Args... args)
			: m_Data{ std::make_tuple(args) }
		{}

		inline void SetData(const Args ... args)
		{
			m_Data = std::make_tuple(args);
		}

		inline const std::tuple<Args...>& GetData() const
		{
			return m_Data;
		}

	private:
		std::tuple<Args...> m_Data;
	};

	class Blackboard final
	{
		using UMapCIt = std::unordered_map<std::string, IBlackboardData*>::const_iterator;
	public:
		Blackboard() = default;

		template<typename ... Args>
		inline void AddData(const std::string& id, const Args... args) noexcept
		{
			const UMapCIt cIt{ m_pData.find(id) };

			if (cIt == m_pData.cend())
				m_pData.insert(std::make_pair(id, new BlackboardData<Args...>{ args }));
#ifdef _DEBUG
			else
				Logger::LogWarning("Blackboard::AddData() did not add data with ID: " + id + " because it was already present!\n");
#endif // _DEBUG
		}

		template<typename ... Args>
		inline const std::tuple<Args...>& GetData(const std::string& id) const noexcept
		{
			const UMapCIt cIt{ m_pData.find(id) };

			if (cIt != m_pData.cend())
				return static_cast<BlackboardData<Args...>*>(cIt->second.get())->GetData();
#ifdef _DEBUG
			else
				Logger::LogWarning("Blackboard::GetData() did not find data with ID: " + id + "\n");
#endif // _DEBUG
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<IBlackboardData>> m_pData;
	};
}

#endif // !INTEGRIAN_BLACKBOARD_H