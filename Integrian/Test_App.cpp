#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "TextureManager.h"
#include "Timer.h"
#include "InputManager.h"
#include "ActorComponent.h"
#include "HealthDisplayComponent.h"
#include "HealthComponent.h"
#include "KillCommand.h"

void Integrian::Test_App::Start()
{
	TextureManager& textureManager{ TextureManager::GetInstance() };

	GameObject* pBackground = new GameObject{};
	textureManager.AddTexture("background", "Images/background.jpg");
	pBackground->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTextures().find("background")->second });
	m_pGameObjects.push_back(std::move(pBackground));

	GameObject* pLogo = new GameObject{};
	textureManager.AddTexture("logo", "Images/logo.png");
	pLogo->AddComponent(new TextureComponent{ TextureManager::GetInstance().GetTextures().find("logo")->second });
	pLogo->transform = Point2f{ 216.f, float(m_WindowHeight) - 180.f };
	m_pGameObjects.push_back(std::move(pLogo));

	GameObject* pTitle = new GameObject{};
	pTitle->AddComponent(new TextComponent{ "Programming 4 Assignment",30,RGBColour{255.f,0.f,0.f} });
	pTitle->transform = Point2f{ 100.f, float(m_WindowHeight) - 70.f };
	m_pGameObjects.push_back(std::move(pTitle));

	GameObject* pFPSCounter = new GameObject{};
	pFPSCounter->AddComponent(new TextComponent{ "FPS: ",10,RGBColour{0.f,255.f,0.f} });
	pFPSCounter->AddComponent(new FPSComponent{ pFPSCounter->GetComponentByType<TextComponent>() });
	pFPSCounter->transform = Point2f{ 10.f,float(m_WindowHeight) - 30.f };
	m_pGameObjects.push_back(std::move(pFPSCounter));

	GameObject* pQbert = new GameObject{};
	GameObject* pQbertHealthDisplay = new GameObject{};

	TextComponent* pText{ new TextComponent{"Remaining Lives: ", 30, RGBColour{255.f,0.f,0.f}} };
	HealthComponent* pHealthComponent{ new HealthComponent{3,3} };
	HealthDisplayComponent* pHealthDisplayComponent{ new HealthDisplayComponent{pText, pHealthComponent} };
	ActorComponent* pActor{ new ActorComponent{} };
	KillCommand* pKillCommand{ new KillCommand{pHealthComponent} };
	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver());
	pActor->AddCommand(GameInput{ KeyboardInput::A }, pKillCommand, State::OnRelease);

	pQbert->AddComponent(pActor);
	pQbert->AddComponent(pHealthComponent);
	pQbertHealthDisplay->transform = Point2f{ 150.f,150.f };

	pQbertHealthDisplay->AddComponent(pText);
	pQbertHealthDisplay->AddComponent(pHealthDisplayComponent);

	m_pGameObjects.push_back(std::move(pQbert));
	m_pGameObjects.push_back(std::move(pQbertHealthDisplay));

	m_pCommands.push_back(std::move(pKillCommand));
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