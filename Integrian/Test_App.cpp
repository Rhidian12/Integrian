#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "TextureManager.h"
#include "Timer.h"

void Integrian::Test_App::Start()
{
	GameObject* pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("background", "Images/background.jpg");
	pGameObject->AddComponent("background", new TextureComponent{ TextureManager::GetInstance().GetTextures().find("background")->second });
	m_pGameObjects.insert(std::move(std::make_pair("Background", pGameObject)));

	pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("logo", "Images/logo.png");
	pGameObject->AddComponent("logo", new TextureComponent{ TextureManager::GetInstance().GetTextures().find("logo")->second });
	pGameObject->transform = Point2f{ 216.f, float(m_WindowHeight) - 180.f };
	m_pGameObjects.insert(std::move(std::make_pair("Logo", pGameObject)));

	pGameObject = new GameObject{};
	pGameObject->AddComponent("Title", new TextComponent{ "Programming 4 Assignment",30,RGBColour{255.f,0.f,0.f} });
	pGameObject->transform = Point2f{ 100.f, float(m_WindowHeight) - 70.f };
	m_pGameObjects.insert(std::move(std::make_pair("Title", pGameObject)));

	pGameObject = new GameObject{};
	pGameObject->AddComponent("FPSCounter", new TextComponent{ "FPS: ",10,RGBColour{0.f,255.f,0.f} });
	pGameObject->AddComponent("FPSLogic", new FPSComponent{ static_cast<TextComponent*>(pGameObject->GetComponentByName("FPSCounter")) });
	pGameObject->transform = Point2f{ 10.f,float(m_WindowHeight) - 30.f };
	m_pGameObjects.insert(std::move(std::make_pair("FPSCounter", pGameObject)));
}

void Integrian::Test_App::Update(const float dt)
{
	for(const std::pair<std::string, GameObject*>& pair : m_pGameObjects)
		pair.second->Update(dt);
}

void Integrian::Test_App::Render() const
{
	for (const std::pair<std::string, GameObject*>& pair : m_pGameObjects)
		pair.second->Render();
}
