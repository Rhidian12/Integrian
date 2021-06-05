#pragma once

#ifndef APP_SELECTOR_H
#define APP_SELECTOR_H

#include <unordered_map> // std::unordered_map
#include "Singleton.h" // Singleton
#include <vector>
#include "ListenerInterface.h" // IListener

namespace Integrian
{
	class App;
	class App_Selector final : public Singleton<App_Selector>, public IListener
	{
	public:
		~App_Selector();
		
		void AddApplication(App* pApplication);
		void SetActiveApplication(const std::string& name);
		void RunActiveApplication();

		void RemoveApplication(const std::string& name);

		bool OnEvent(const Event& event) override;

		[[nodiscard]] App* GetActiveApplication() const;

	private:
		App_Selector();
		friend class Singleton<App_Selector>;

		std::unordered_map<std::string, App*> m_pApplications{};
		std::vector<App*> m_pApplicationsToDelete{};
		App* m_pActiveApplication{};
	};
}

#endif // !APP_SELECTOR_H