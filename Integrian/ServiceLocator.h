#pragma once

#ifndef INTEGRIAN_SERVICELOCATOR_H
#define INTEGRIAN_SERVICELOCATOR_H

#include <unordered_set> // std::unordered_set
#include <typeinfo> // typeid()
#include "ServiceInterface.h" // Base class for all services
#include "Logger.h" // Logger
#include "NullService.h" // NullService
#include <type_traits> // std::is_base_of, std::is_same_v

namespace Integrian
{
	class ServiceLocator final
	{
	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;

		static void Cleanup();

		template<typename Type>
		[[nodiscard]] inline static Type* GetService()
		{
			for (IService* pService : m_pServices)
				if (typeid(*pService) == typeid(Type))
					return static_cast<Type*>(pService);

			Logger::GetInstance().Log("GetService returned a nullservice\n", ErrorLevel::warning);
			return static_cast<NullService*>(m_pNullService);
		}

		// the commented part is sfinae
		template<typename Type/*, typename = std::enable_if_t<std::is_base_of_v<IService, Type>>*/> // this is templated so it can be checked at compile time
		inline static void Provide(Type* pService)
		{
			if constexpr (std::is_base_of_v<IService, Type>)
			{
				Logger& logger{ Logger::GetInstance() };
				if (pService == nullptr || std::is_same_v<Type, NullService>) // literally this if-statement is the reason I made this templated
				{
					logger.Log("A NullService is always present in the ServiceLocator!", ErrorLevel::warning);
					return; // we already inserted a nullservice
				}

				if (m_pServices.find(pService) != m_pServices.cend())
				{
					logger.Log("The service: ", ErrorLevel::warning);
					logger.Log(typeid(pService).name(), ErrorLevel::warning);
					logger.Log(" was already provided", ErrorLevel::warning);
				}
				else
					m_pServices.insert(pService);
			}
			else
				static_assert(std::is_base_of_v<IService, Type>, "The pointer supplied to ServiceLocator::Provide was not a Service"); // compile time assertion
		}

	private:
		inline static std::unordered_set<IService*> m_pServices{};
		inline static IService* m_pNullService{ new NullService{} };
	};
}

#endif // !INTEGRIAN_SERVICELOCATOR_H