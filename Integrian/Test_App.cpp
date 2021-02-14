#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TextureManager.h"
#include "Timer.h"

void Integrian::Test_App::Start()
{
	GameObject* pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("background", "Images/background.jpg");
	pGameObject->AddComponent("background", new TextureComponent{ TextureManager::GetInstance().GetTextures().find("background")->second });
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("logo", "Images/logo.png");
	pGameObject->AddComponent("logo", new TextureComponent{ TextureManager::GetInstance().GetTextures().find("logo")->second });
	pGameObject->transform = Point2f{ 216.f, float(m_WindowHeight) - 180.f };
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	pGameObject->AddComponent("Title", new TextComponent{ "Programming 4 Assignment",30,RGBColour{255.f,0.f,0.f} });
	pGameObject->transform = Point2f{ 100.f, float(m_WindowHeight) - 70.f };
	m_pGameObjects.push_back(std::move(pGameObject));
}

void Integrian::Test_App::Render() const
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
