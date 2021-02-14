#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TextureManager.h"
#include "Timer.h"

void Integrian::Test_App::Start()
{
	GameObject* pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("background", "Data/Background/Background.png");
	pGameObject->AddComponent("background", new TextureComponent{ TextureManager::GetInstance().GetTextures().find("background")->second });
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	pGameObject->AddComponent("FPS", new TextComponent{"Test"});
	pGameObject->transform = Point2f{ 150.f,150.f };
	m_pGameObjects.push_back(std::move(pGameObject));
}

void Integrian::Test_App::Update(const float elapsedSeconds)
{
	for (GameObject* pGameObject : m_pGameObjects)
	{
		TextComponent* pTextComponent{ pGameObject->GetComponentByType<TextComponent>() };
		if (pTextComponent)
		{
			pTextComponent->SetTextToRender(std::to_string(Timer::GetInstance().GetFPS()));
		}
	}
}

void Integrian::Test_App::Render() const
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
