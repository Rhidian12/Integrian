#include "IntegrianPCH.h"
#include "Test_App_2_Boogaloo.h"
#include "App_Selector.h"
#include "TextureComponent.h"
#include "TextureManager.h"
#include "EventQueue.h"
#include "InputManager.h"

Integrian::Test_App_2_Boogaloo::Test_App_2_Boogaloo()
	: App{ "Test_App_2_Boogaloo" }
{

}

void Integrian::Test_App_2_Boogaloo::Start()
{
	m_Commands["SwitchToTest_Scene"] = [this]()
	{
		EventQueue::GetInstance().QueueEvent(Event{ "Change_Application", "Test_App" });
	};

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::G }, m_Commands["SwitchToTest_Scene"], State::OnRelease);

	TextureManager::GetInstance().AddTexture("Sabaton", "Images/Sabaton.jpg");

	GameObject* pGameObject{ new GameObject{} };
	pGameObject->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTexture("Sabaton") });
	m_pGameObjects.push_back(pGameObject);
}

void Integrian::Test_App_2_Boogaloo::Render() const
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
