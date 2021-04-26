#include "Test_App.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "TextureManager.h"
#include "Timer.h"
#include "InputManager.h"
#include "HealthDisplayComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "Logger.h"
#include "SDLAudioSystem.h"
#include "AudioLocator.h"
#include "EventQueue.h"
#include "App_Selector.h"

Integrian::Test_App::Test_App()
	: App{ "Test_App" }
{
}

void Integrian::Test_App::Start()
{
	TextureManager& textureManager{ TextureManager::GetInstance() };

	GameObject* pBackground = new GameObject{};
	textureManager.AddTexture("background", "Images/background.jpg");
	pBackground->AddComponent(new TextureComponent{ textureManager.GetTextures().find("background")->second });
	m_pGameObjects.push_back(std::move(pBackground));

	GameObject* pLogo = new GameObject{};
	textureManager.AddTexture("logo", "Images/logo.png");
	pLogo->AddComponent(new TextureComponent{ textureManager.GetTextures().find("logo")->second });
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

	InitPlayerOne();
	InitPlayerTwo();

	AudioLocator::Provide(new SDLAudioSystem{});
	AudioSystem* pAudio = AudioLocator::GetAudio();
	pAudio->AddMusic("Data/AHHHHH.mp3");
	pAudio->PlayMusic(0);
	pAudio->AddSound("Data/menu3.wav");
	EventQueue::GetInstance().AddListener(pAudio);

	m_Commands["SwitchToTest_App_2_Scene"] = [this]()
	{
		EventQueue::GetInstance().QueueEvent(Event{ "Change_Application", "Test_App_2_Boogaloo" });
	};

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::G }, m_Commands["SwitchToTest_App_2_Scene"], State::OnRelease);
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

	ImGui::SetNextWindowPos(ImVec2{ 250,0 });
	ImGui::Begin("Player 1 uses the keyboard");
	ImGui::Text("Press A To Damage Q*bert, This will also play a sound");
	ImGui::Text("Press W To Defeat Coily");
	ImGui::Text("Press S To Catch Slick Or Sam");
	ImGui::Text("Press D To Change The Colour");
	ImGui::Text("Press E To Add The Remaining Disks To The Score");
	ImGui::Text("This is all hardcoded and just adds score");
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2{ 250,150 });
	ImGui::Begin("Player 2 uses the controller");
	ImGui::Text("Press A To Damage Q*bert");
	ImGui::Text("Press B To Defeat Coily");
	ImGui::Text("Press X To Catch Slick Or Sam");
	ImGui::Text("Press Y To Change The Colour");
	ImGui::Text("Press RightTrigger To Add The Remaining Disks To The Score");
	ImGui::Text("This is all hardcoded and just adds score");
	ImGui::End();
}

void Integrian::Test_App::InitPlayerOne()
{
	GameObject* pQbert = new GameObject{};
	GameObject* pQbertHealthDisplay = new GameObject{};
	GameObject* pScoreDisplay{ new GameObject{} };

	TextComponent* pTextComponent{ new TextComponent{"Player 1 Remaining Lives: ", 30, RGBColour{255.f,0.f,0.f}} };
	HealthComponent* pHealthComponent{ new HealthComponent{3,3} };
	HealthDisplayComponent* pHealthDisplayComponent{ new HealthDisplayComponent{pTextComponent, pHealthComponent->GetCurrentHealth()} };
	ScoreComponent* pScoreComponent{ new ScoreComponent{} };

	TextComponent* pScoreDisplayTextComponent{ new TextComponent{"Player 1 Score: ", 30, RGBColour{255.f,0.f,0.f}} };
	ScoreDisplayComponent* pScoreDisplayComponent{ new ScoreDisplayComponent{pScoreDisplayTextComponent, 0 } };
	pScoreDisplay->AddComponent(pScoreDisplayTextComponent);
	pScoreDisplay->AddComponent(pScoreDisplayComponent);
	pScoreDisplay->transform = Point2f{ 150.f, 50.f };

	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver());
	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver<uint64_t>());
	pScoreComponent->AddObserver(pScoreDisplayComponent->GetObserver());

	m_Commands["KillCommandPlayerOne"] = [this, pHealthComponent]()
		{
			pHealthComponent->DecreaseLivesByValue(1);
			EventQueue::GetInstance().QueueEvent(Event{ "PlaySound", 0, false, 0, 100 });
		};
	m_Commands["DefeatCoilyCommandPlayerOne"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::CoilyDefeated);
		};
	m_Commands["CatchSlickOrSamCommandPlayerOne"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::CatchingSlickAndSam);
		};
	m_Commands["ChangeColourCommandPlayerOne"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::ColourChange);
		};
	m_Commands["DisksRemainingCommandPlayerOne"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::RemainingDiscs);
		};

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::A }, m_Commands["KillCommandPlayerOne"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::W }, m_Commands["DefeatCoilyCommandPlayerOne"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::S }, m_Commands["CatchSlickOrSamCommandPlayerOne"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::D }, m_Commands["ChangeColourCommandPlayerOne"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::E }, m_Commands["DisksRemainingCommandPlayerOne"], State::OnRelease);

	pQbert->AddComponent(pHealthComponent);
	pQbert->AddComponent(pScoreComponent);
	pQbertHealthDisplay->transform = Point2f{ 150.f,150.f };

	pQbertHealthDisplay->AddComponent(pTextComponent);
	pQbertHealthDisplay->AddComponent(pHealthDisplayComponent);

	m_pGameObjects.push_back(std::move(pQbert));
	m_pGameObjects.push_back(std::move(pQbertHealthDisplay));
	m_pGameObjects.push_back(std::move(pScoreDisplay));
}

void Integrian::Test_App::InitPlayerTwo()
{
	GameObject* pQbert = new GameObject{};
	GameObject* pQbertHealthDisplay = new GameObject{};
	GameObject* pScoreDisplay{ new GameObject{} };

	TextComponent* pTextComponent{ new TextComponent{"Player 2 Remaining Lives: ", 30, RGBColour{255.f,0.f,0.f}} };
	HealthComponent* pHealthComponent{ new HealthComponent{3,3} };
	HealthDisplayComponent* pHealthDisplayComponent{ new HealthDisplayComponent{pTextComponent, pHealthComponent->GetCurrentHealth()} };
	ScoreComponent* pScoreComponent{ new ScoreComponent{} };

	TextComponent* pScoreDisplayTextComponent{ new TextComponent{"Player 2 Score: ", 30, RGBColour{255.f,0.f,0.f}} };
	ScoreDisplayComponent* pScoreDisplayComponent{ new ScoreDisplayComponent{pScoreDisplayTextComponent, 0 } };

	pScoreDisplay->AddComponent(pScoreDisplayTextComponent);
	pScoreDisplay->AddComponent(pScoreDisplayComponent);
	pScoreDisplay->transform = Point2f{ 150.f, 0.f };

	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver());
	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver<uint64_t>());
	pScoreComponent->AddObserver(pScoreDisplayComponent->GetObserver());

	m_Commands["KillCommandPlayerTwo"] = [this, pHealthComponent]()
		{
			pHealthComponent->DecreaseLivesByValue(1);
			EventQueue::GetInstance().QueueEvent(Event{ "PlaySound", 0, false, 0, 100 });
		};
	m_Commands["DefeatCoilyCommandPlayerTwo"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::CoilyDefeated);
		};
	m_Commands["CatchSlickOrSamCommandPlayerTwo"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::CatchingSlickAndSam);
		};
	m_Commands["ChangeColourCommandPlayerTwo"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::ColourChange);
		};
	m_Commands["DisksRemainingCommandPlayerTwo"] = [pScoreComponent]()
		{
			pScoreComponent->ChangeScore(TypeOfGettingScore::RemainingDiscs);
		};

	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::ButtonA },		m_Commands["KillCommandPlayerTwo"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::ButtonB },		m_Commands["DefeatCoilyCommandPlayerTwo"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::ButtonX },		m_Commands["CatchSlickOrSamCommandPlayerTwo"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::ButtonY },		m_Commands["ChangeColourCommandPlayerTwo"], State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::RightTrigger },	m_Commands["DisksRemainingCommandPlayerTwo"], State::OnRelease);

	pQbert->AddComponent(pHealthComponent);
	pQbert->AddComponent(pScoreComponent);

	pQbertHealthDisplay->transform = Point2f{ 150.f,100.f };
	pQbertHealthDisplay->AddComponent(pTextComponent);
	pQbertHealthDisplay->AddComponent(pHealthDisplayComponent);

	m_pGameObjects.push_back(std::move(pQbert));
	m_pGameObjects.push_back(std::move(pQbertHealthDisplay));
	m_pGameObjects.push_back(std::move(pScoreDisplay));
}
