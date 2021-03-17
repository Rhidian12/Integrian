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
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "DefeatCoilyCommand.h"
#include "CatchSlickOrSamCommand.h"
#include "ChangeColourCommand.h"
#include "DisksRemainingCommand.h"
#include "Logger.h"

void Integrian::Test_App::Start()
{
	TextureManager textureManager{ ServiceLocator::GetInstance().GetTextureManager() };

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
	ImGui::Text("Press A To Damage Q*bert");
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
	ActorComponent* pActor{ new ActorComponent{} };
	ScoreComponent* pScoreComponent{ new ScoreComponent{} };

	TextComponent* pScoreDisplayTextComponent{ new TextComponent{"Player 1 Score: ", 30, RGBColour{255.f,0.f,0.f}} };
	ScoreDisplayComponent* pScoreDisplayComponent{ new ScoreDisplayComponent{pScoreDisplayTextComponent, 0 } };
	pScoreDisplay->AddComponent(pScoreDisplayTextComponent);
	pScoreDisplay->AddComponent(pScoreDisplayComponent);
	pScoreDisplay->transform = Point2f{ 150.f, 50.f };

	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver());
	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver<uint64_t>());
	pScoreComponent->AddObserver(pScoreDisplayComponent->GetObserver());

	KillCommand* pKillCommand{ new KillCommand{pHealthComponent} };
	DefeatCoilyCommand* pDefeatCoilyCommand{ new DefeatCoilyCommand{pScoreComponent} };
	CatchSlickOrSamCommand* pCatchSlickOrSamCommand{ new CatchSlickOrSamCommand{pScoreComponent} };
	ChangeColourCommand* pChangeColourCommand{ new ChangeColourCommand{pScoreComponent} };
	DisksRemainingCommand* pDisksRemainingCommand{ new DisksRemainingCommand{pScoreComponent} };
<<<<<<< HEAD
	CommandManager commandManager = ServiceLocator::GetInstance().GetCommandManager();
	commandManager.AddCommand(pKillCommand);
	commandManager.AddCommand(pDefeatCoilyCommand);
	commandManager.AddCommand(pCatchSlickOrSamCommand);
	commandManager.AddCommand(pChangeColourCommand);
	commandManager.AddCommand(pDisksRemainingCommand);

	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonA }, pKillCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonB }, pDefeatCoilyCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonX }, pCatchSlickOrSamCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonY }, pChangeColourCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::RightTrigger }, pDisksRemainingCommand, State::OnRelease);
=======

	pActor->AddCommand(GameInput{ KeyboardInput::A }, pKillCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ KeyboardInput::W }, pDefeatCoilyCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ KeyboardInput::S }, pCatchSlickOrSamCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ KeyboardInput::D }, pChangeColourCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ KeyboardInput::E }, pDisksRemainingCommand, State::OnRelease);
>>>>>>> parent of 9f32a8a (Made CommandManager BUT NEEDS EVENT QUEUE TO BE FINISHED)

	pQbert->AddComponent(pActor);
	pQbert->AddComponent(pHealthComponent);
	pQbert->AddComponent(pScoreComponent);
	pQbertHealthDisplay->transform = Point2f{ 150.f,150.f };

	pQbertHealthDisplay->AddComponent(pTextComponent);
	pQbertHealthDisplay->AddComponent(pHealthDisplayComponent);

	m_pGameObjects.push_back(std::move(pQbert));
	m_pGameObjects.push_back(std::move(pQbertHealthDisplay));
	m_pGameObjects.push_back(std::move(pScoreDisplay));

	m_pCommands.push_back(std::move(pKillCommand));
	m_pCommands.push_back(std::move(pDefeatCoilyCommand));
	m_pCommands.push_back(std::move(pCatchSlickOrSamCommand));
	m_pCommands.push_back(std::move(pChangeColourCommand));
	m_pCommands.push_back(std::move(pDisksRemainingCommand));
}

void Integrian::Test_App::InitPlayerTwo()
{
	GameObject* pQbert = new GameObject{};
	GameObject* pQbertHealthDisplay = new GameObject{};
	GameObject* pScoreDisplay{ new GameObject{} };

	TextComponent* pTextComponent{ new TextComponent{"Player 2 Remaining Lives: ", 30, RGBColour{255.f,0.f,0.f}} };
	HealthComponent* pHealthComponent{ new HealthComponent{3,3} };
	HealthDisplayComponent* pHealthDisplayComponent{ new HealthDisplayComponent{pTextComponent, pHealthComponent->GetCurrentHealth()} };
	ActorComponent* pActor{ new ActorComponent{} };
	ScoreComponent* pScoreComponent{ new ScoreComponent{} };

	TextComponent* pScoreDisplayTextComponent{ new TextComponent{"Player 2 Score: ", 30, RGBColour{255.f,0.f,0.f}} };
	ScoreDisplayComponent* pScoreDisplayComponent{ new ScoreDisplayComponent{pScoreDisplayTextComponent, 0 } };
	
	pScoreDisplay->AddComponent(pScoreDisplayTextComponent);
	pScoreDisplay->AddComponent(pScoreDisplayComponent);
	pScoreDisplay->transform = Point2f{ 150.f, 0.f };

	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver());
	pHealthComponent->AddObserver(pHealthDisplayComponent->GetObserver<uint64_t>());
	pScoreComponent->AddObserver(pScoreDisplayComponent->GetObserver());

	KillCommand* pKillCommand{ new KillCommand{pHealthComponent} };
	DefeatCoilyCommand* pDefeatCoilyCommand{ new DefeatCoilyCommand{pScoreComponent} };
	CatchSlickOrSamCommand* pCatchSlickOrSamCommand{ new CatchSlickOrSamCommand{pScoreComponent} };
	ChangeColourCommand* pChangeColourCommand{ new ChangeColourCommand{pScoreComponent} };
	DisksRemainingCommand* pDisksRemainingCommand{ new DisksRemainingCommand{pScoreComponent} };
<<<<<<< HEAD
	CommandManager commandManager = ServiceLocator::GetInstance().GetCommandManager();
	commandManager.AddCommand(pKillCommand);
	commandManager.AddCommand(pDefeatCoilyCommand);
	commandManager.AddCommand(pCatchSlickOrSamCommand);
	commandManager.AddCommand(pChangeColourCommand);
	commandManager.AddCommand(pDisksRemainingCommand);

	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonA }, pKillCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonB }, pDefeatCoilyCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonX }, pCatchSlickOrSamCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::ButtonY }, pChangeColourCommand, State::OnRelease);
	commandManager.LinkCommandToInput(GameInput{ ControllerInput::RightTrigger }, pDisksRemainingCommand, State::OnRelease);
=======

	pActor->AddCommand(GameInput{ ControllerInput::ButtonA }, pKillCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ ControllerInput::ButtonB }, pDefeatCoilyCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ ControllerInput::ButtonX }, pCatchSlickOrSamCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ ControllerInput::ButtonY }, pChangeColourCommand, State::OnRelease);
	pActor->AddCommand(GameInput{ ControllerInput::RightTrigger }, pDisksRemainingCommand, State::OnRelease);
>>>>>>> parent of 9f32a8a (Made CommandManager BUT NEEDS EVENT QUEUE TO BE FINISHED)

	pQbert->AddComponent(pActor);
	pQbert->AddComponent(pHealthComponent);
	pQbert->AddComponent(pScoreComponent);

	pQbertHealthDisplay->transform = Point2f{ 150.f,100.f };
	pQbertHealthDisplay->AddComponent(pTextComponent);
	pQbertHealthDisplay->AddComponent(pHealthDisplayComponent);

	m_pGameObjects.push_back(std::move(pQbert));
	m_pGameObjects.push_back(std::move(pQbertHealthDisplay));
	m_pGameObjects.push_back(std::move(pScoreDisplay));

	m_pCommands.push_back(std::move(pKillCommand));
	m_pCommands.push_back(std::move(pDefeatCoilyCommand));
	m_pCommands.push_back(std::move(pCatchSlickOrSamCommand));
	m_pCommands.push_back(std::move(pChangeColourCommand));
	m_pCommands.push_back(std::move(pDisksRemainingCommand));
}
