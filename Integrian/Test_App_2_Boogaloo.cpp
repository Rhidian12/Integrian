#include "Test_App_2_Boogaloo.h"
#include "App_Selector.h"
#include "TextureComponent.h"
#include "TextureManager.h"

Integrian::Test_App_2_Boogaloo::Test_App_2_Boogaloo()
	: App{ "Test_App_2_Boogaloo" }
{
	m_AppInfo.commandManager.AddCommand("SwitchScenes", [this]()
		{
			m_AppInfo.eventQueue.QueueEvent(Event{ "Change_Application", "Test_App" });
		});

	m_AppInfo.commandManager.LinkCommandToInput(GameInput{ KeyboardInput::G }, "SwitchScenes", State::OnRelease);
	TextureManager::GetInstance().AddTexture("Sabaton", "Images/Sabaton.jpg");
}

void Integrian::Test_App_2_Boogaloo::Start()
{
	GameObject* pGameObject{ new GameObject{} };
	pGameObject->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTexture("Sabaton") });
	m_pGameObjects.push_back(pGameObject);
}

void Integrian::Test_App_2_Boogaloo::Render() const
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
