#include "IntegrianPCH.h" // precompiled header
#include "App_Selector.h" // Header
#include "App.h" // App
#include "EventQueue.h" // EventQueue
#include "Timer.h" // Timer

Integrian::App_Selector::~App_Selector()
{
	for (std::pair<std::string, App*> pApp : m_pApplications)
		SafeDelete(pApp.second);
}

void Integrian::App_Selector::AddApplication(App* pApplication)
{
	if (m_pApplications.insert(std::make_pair(pApplication->GetAppName(), pApplication)).second)
	{
		pApplication->GetAppInfo().eventQueue.AddListener(this);

		if (!m_pActiveApplication)
			m_pActiveApplication = pApplication;
	}
}

void Integrian::App_Selector::SetActiveApplication(const std::string& name)
{
#ifdef _DEBUG
	std::unordered_map<std::string, App*>::const_iterator cIt{ m_pApplications.find(name) };
	if (cIt != m_pApplications.cend())
		m_pActiveApplication = cIt->second;
	else
		Logger::LogSevereError("Application with name: " + name + " was not found!\n");

#else
	m_pActiveApplication = m_pActiveApplication.find(name)->second;
#endif // _DEBUG
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
