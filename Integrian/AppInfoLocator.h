#pragma once

#ifndef INTEGRIAN_APPINFO_LOCATOR_H
#define INTEGRIAN_APPINFO_LOCATOR_H

#include "pch.h" // AlwaysFalse()
#include "App_Info.h" // App_Info. This is included and not forward declared, so people don't have to include both AppInfoLocator and App_Info

namespace Integrian
{
	class AppInfoLocator final
	{
	public:
		static App_Info* GetAppInfo();

		template<typename Type>
		static void Provide(Type* pAppInfo)
		{
			if constexpr (std::is_same_v<Type, App_Info>)
				m_pAppInfo = pAppInfo;
			else if (pAppInfo == nullptr)
				m_pAppInfo = nullptr;
			else
				static_assert(AlwaysFalse(), "The pointer supplied to AudioLocator::Provide() was not an AudioSystem");
		}

	private:
		AppInfoLocator() = default;

		inline static App_Info* m_pAppInfo{};
	};
}

#endif // !INTEGRIAN_APPINFO_LOCATOR_H