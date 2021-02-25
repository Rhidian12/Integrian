#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "TextureManager.h"
#include "Timer.h"
#include "TestCommand.h"
#include "InputManager.h"
#include "ActorComponent.h"
#include "HealthComponent.h"
#include "KillCommand.h"

void Integrian::Test_App::Start()
{
	GameObject* pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("background", "Images/background.jpg");
	pGameObject->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTextures().find("background")->second });
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	TextureManager::GetInstance().AddTexture("logo", "Images/logo.png");
	pGameObject->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTextures().find("logo")->second });
	pGameObject->transform = Point2f{ 216.f, float(m_WindowHeight) - 180.f };
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	pGameObject->AddComponent(new TextComponent{ "Programming 4 Assignment",30,RGBColour{255.f,0.f,0.f} });
	pGameObject->transform = Point2f{ 100.f, float(m_WindowHeight) - 70.f };
	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};
	pGameObject->AddComponent(new TextComponent{ "FPS: ",10,RGBColour{0.f,255.f,0.f} });
	pGameObject->AddComponent(new FPSComponent{ pGameObject->GetComponentByType<TextComponent>() });
	pGameObject->transform = Point2f{ 10.f,float(m_WindowHeight) - 30.f };

	Command* pCommand = new TestCommand{ pGameObject->GetComponentByType<FPSComponent>() };
	m_pCommands.push_back(std::move(pCommand));

	m_pGameObjects.push_back(std::move(pGameObject));

	pGameObject = new GameObject{};

	HealthComponent* pHealth{ new HealthComponent{3} };
	ActorComponent* pActor{ new ActorComponent{} };
	KillCommand* pKillCommand{ new KillCommand{pActor} };
	pActor->AddCommand(GameInput{ ControllerInput::ButtonA }, pKillCommand, State::OnRelease);
	pGameObject->AddComponent(std::move(pActor));
	pGameObject->AddComponent(std::move(pHealth));
}

void Integrian::Test_App::Update(const float dt)
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Update(dt);
}

void Integrian::Test_App::Render() const
{
	for (GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();

	ImGui::Begin("Test_App");
	ImGui::Button("Single Player");
	ImGui::Button("Co-op");
	ImGui::Button("Versus");
	ImGui::End();
}