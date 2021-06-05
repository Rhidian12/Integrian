#include "IntegrianPCH.h" // precompiled header
#include "App_Selector.h" // Header
#include "App.h" // App
#include "EventQueue.h" // EventQueue
#include "Timer.h" // Timer

extern std::atomic<bool> volatile g_IsLooping;

Integrian::App_Selector::App_Selector()
{
	EventQueue::GetInstance().AddListener(this);
}

Integrian::App_Selector::~App_Selector()
{
	for (std::pair<std::string, App*> pApp : m_pApplications)
		SafeDelete(pApp.second);
}

void Integrian::App_Selector::AddApplication(App* pApplication)
{
	if (m_pApplications.insert(std::make_pair(pApplication->GetAppName(), pApplication)).second)
	{
		if (!m_pActiveApplication)
			SetActiveApplication(pApplication->GetAppName());
	}
}

void Integrian::App_Selector::SetActiveApplication(const std::string& name)
{
	if (m_pActiveApplication && name == m_pActiveApplication->GetAppName())
		return;
#ifdef _DEBUG
	std::unordered_map<std::string, App*>::const_iterator cIt{ m_pApplications.find(name) };
	if (cIt != m_pApplications.cend())
	{
		if(m_pActiveApplication)
			m_pActiveApplication->AppExit(); // first call the old app (if there is an old app) its OnAppExit()

		m_pActiveApplication = cIt->second; // Set new application
		m_pActiveApplication->AppEnter(); // Call new application its OnAppEnter()
	}
	else
		Logger::LogSevereError("Application with name: " + name + " was not found!\n");

#else
	m_pActiveApplication = m_pApplications.find(name)->second;
#endif // _DEBUG
}

void Integrian::App_Selector::RunActiveApplication()
{
	while(g_IsLooping.load())
		m_pActiveApplication->Run();
}

bool Integrian::App_Selector::OnEvent(const Event& event)
{
	if (event.GetEvent() == "Change_Application")
	{
		SetActiveApplication(std::get<0>(event.GetData<const char*>()));
		return true;
	}
	else
		return false;
}

Integrian::App* Integrian::App_Selector::GetActiveApplication() const
{
	return m_pActiveApplication;
}
