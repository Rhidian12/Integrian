#pragma once

#ifndef INTEGRIAN_SERVICELOCATOR_H
#define INTEGRIAN_SERVICELOCATOR_H

#include "pch.h" // AlwaysFalse()
#include <unordered_set> // std::unordered_set
#include <typeinfo> // typeid()
#include "ServiceInterface.h" // Base class for all services
#include "Logger.h" // Logger
#include "NullService.h" // NullService
#include <type_traits> // std::is_base_of, std::is_same_v
#include "AudioPlayerLogged.h" // AudioPlayerLogged

namespace Integrian
{
	class ServiceLocator final
	{
	public:
		ServiceLocator() = default;
		~ServiceLocator() = default;

		static void Cleanup();

		[[nodiscard]] inline static AudioSystem* GetAudio()
		{
			for (IService* pService : m_pServices)
				if (typeid(*pService) == typeid(AudioPlayerLogged))
					return static_cast<AudioSystem*>(pService);

			Logger::LogWarning("GetAudio returned a nullservice\n");
			return static_cast<NullService*>(m_pNullService);
		}

		// the commented part is sfinae
		template<typename Type/*, typename = std::enable_if_t<std::is_base_of_v<IService, Type>>*/> // this is templated so it can be checked at compile time
		inline static void Provide(Type* pService)
		{
			if constexpr (std::is_base_of_v<IService, Type>)
			{
				if (pService == nullptr || std::is_same_v<Type, NullService>) // literally this if-statement is the reason I made this templated
				{
					Logger::LogWarning("A NullService is always present in the ServiceLocator!\n");
					return; // we already inserted a nullservice
				}

				if (m_pServices.find(pService) != m_pServices.cend())
					Logger::LogWarning(std::string{ "The service: " } + typeid(pService).name() + " was already provided!\n");
				else
					m_pServices.insert(pService);
			}
			else
				static_assert(AlwaysFalse(), "The pointer supplied to ServiceLocator::Provide was not a Service"); // compile time assertion
		}

	private:
		inline static std::unordered_set<IService*> m_pServices{};
		inline static IService* m_pNullService{ new NullService{} };
	
		using USetConstIterator = std::unordered_set<IService*>::const_iterator;
	};
}

#endif // !INTEGRIAN_SERVICELOCATOR_H