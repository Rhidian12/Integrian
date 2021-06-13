#include "IntegrianPCH.h" // precompiled header
#include "App_Manager.h" // Header
#include "App.h" // App
#include "EventQueue.h" // EventQueue
#include "Timer.h" // Timer
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector

extern std::atomic<bool> volatile g_IsLooping;

namespace Integrian
{
	class App_Manager::App_Manager_Implementation final
	{
	public:
		~App_Manager_Implementation()
		{
			for (std::pair<std::string, App*> pApp : m_pApplications)
				SafeDelete(pApp.second);

			for (App* pApp : m_pApplicationsToDelete)
				SafeDelete(pApp);
		}

		void AddApplication(App* pApplication)
		{
			std::unordered_map<std::string, App*>::const_iterator cIt{ m_pApplications.find(pApplication->GetAppName()) };

			if (cIt == m_pApplications.cend())
			{
				m_pApplications.insert(std::make_pair(pApplication->GetAppName(), pApplication)).second;
				if (!m_pActiveApplication)
					SetActiveApplication(pApplication->GetAppName());
			}
			else
				Logger::LogError(std::string{ "App_Selector::AddApplication() > Error when trying to add Application with name: " }
			+ pApplication->GetAppName() + ", it was already present!");
		}
		void SetActiveApplication(const std::string& name)
		{
			if (m_pActiveApplication && (name == m_pActiveApplication->GetAppName()))
				return;

			std::unordered_map<std::string, App*>::const_iterator cIt{ m_pApplications.find(name) };
			if (cIt != m_pApplications.cend())
			{
				if (m_pActiveApplication)
					m_pActiveApplication->AppExit(); // first call the old app (if there is an old app) its OnAppExit()

				m_pActiveApplication = cIt->second; // Set new application
				m_pActiveApplication->AppEnter(); // Call new application its OnAppEnter()
			}
			else
				Logger::LogSevereError("Application with name: " + name + " was not found!\n");
		}
		void RunActiveApplication()
		{
			while (g_IsLooping.load())
				m_pActiveApplication->Run();
		}

		void RemoveApplication(const std::string& name)
		{
			assert(m_pActiveApplication->GetAppName() != name);

			std::unordered_map<std::string, App*>::const_iterator cIt{ m_pApplications.find(name) };
			if (cIt != m_pApplications.cend())
			{
				m_pApplicationsToDelete.push_back(m_pApplications[name]);
				Erase_If(m_pApplications, [name](const std::pair<std::string, App*>& pair)->bool
					{
						return pair.first == name;
					});
			}
			else
				Logger::LogSevereError("App_Selector::RemoveApplication() > Application with name: " + name + " was not found!\n");
		}

		[[nodiscard]] App* GetActiveApplication() const
		{
			return m_pActiveApplication;
		}

	private:
		std::unordered_map<std::string, App*> m_pApplications{};
		std::vector<App*> m_pApplicationsToDelete{};
		App* m_pActiveApplication{};
	};
}

Integrian::App_Manager::App_Manager()
	: m_pImplementation{}
{
	EventQueue::GetInstance().AddListener(this);
}

Integrian::App_Manager::~App_Manager()
{
	SafeDelete(m_pImplementation);
}

Integrian::App_Manager& Integrian::App_Manager::GetInstance()
{
	static App_Manager instance{};
	return instance;
}

void Integrian::App_Manager::AddApplication(App* pApplication)
{
	m_pImplementation->AddApplication(pApplication);
}

void Integrian::App_Manager::SetActiveApplication(const char* pName)
{
	m_pImplementation->SetActiveApplication(pName);
}

void Integrian::App_Manager::RunActiveApplication()
{
	m_pImplementation->RunActiveApplication();
}

void Integrian::App_Manager::RemoveApplication(const char* pName)
{
	m_pImplementation->RemoveApplication(pName);
}

bool Integrian::App_Manager::OnEvent(const Event& event)
{
	if (event.GetEvent() == "Change_Application")
	{
		SetActiveApplication(std::get<0>(event.GetData<const char*>()));
		return true;
	}
	else
		return false;
}

Integrian::App* Integrian::App_Manager::GetActiveApplication() const
{
	return m_pImplementation->GetActiveApplication();
}
