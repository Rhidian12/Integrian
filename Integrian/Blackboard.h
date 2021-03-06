#pragma once

#ifndef INTEGRIAN_BLACKBOARD_H
#define INTEGRIAN_BLACKBOARD_H

#include "IntegrianPCH.h"
#include <unordered_map> // std::unordered_map
#include <memory> // std::shared_ptr

namespace Integrian
{
	class IBlackboardData
	{
	public:
		virtual ~IBlackboardData() = default;
	};

	template<typename Type>
	class BlackboardData final : public IBlackboardData
	{
	public:
		BlackboardData(const Type data)
			: m_Data{ data }
		{}

		inline void SetData(const Type data)
		{
			m_Data = data;
		}

		inline const Type GetData() const noexcept
		{
			return m_Data;
		}

	private:
		Type m_Data;
	};

	class Blackboard final
	{
		using UMapCIt = std::unordered_map<std::string, std::shared_ptr<IBlackboardData>>::const_iterator;
	public:
		Blackboard() = default;

		template<typename Type>
		inline void AddData(const std::string& id, const Type data) noexcept
		{
			const UMapCIt cIt{ m_pData.find(id) };

			if (cIt == m_pData.cend())
				m_pData.insert(std::make_pair(id, new BlackboardData<Type>{ data }));
#ifdef _DEBUG
			else
				Logger::LogWarning("Blackboard::AddData() did not add data with ID: " + id + " because it was already present!\n");
#endif // _DEBUG
		}

		template<typename Type>
		inline void ChangeData(const std::string& id, const Type data) noexcept
		{
			const UMapCIt cIt{ m_pData.find(id) };
			if (cIt != m_pData.cend())
				static_cast<BlackboardData<Type>*>(m_pData[id].get())->SetData(data);
#ifdef _DEBUG
			else
				Logger::LogWarning("Blackboard::ChangeData() did not change data with ID: " + id + " because it was not present!\n");
#endif // _DEBUG
		}

		template<typename Type>
		inline const Type GetData(const std::string& id) noexcept
		{
			const UMapCIt cIt{ m_pData.find(id) };

			if (cIt != m_pData.cend())
				return static_cast<BlackboardData<Type>*>(m_pData[id].get())->GetData();
#ifdef _DEBUG
			else
				Logger::LogWarning("Blackboard::GetData() did not find data with ID: " + id + "\n");
#endif // _DEBUG
			return Type{};
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<IBlackboardData>> m_pData;
	};
}

#endif // !INTEGRIAN_BLACKBOARD_H