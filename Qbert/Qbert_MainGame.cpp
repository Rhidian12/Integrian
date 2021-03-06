#include "Qbert_MainGame.h"
#include <Texture.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include "PyramidComponent.h"
#include "QbertMovementComponent.h"
#include "TileFactoryComponent.h"
#include "QbertSpriteComponent.h"
#include <Utility Functions.h>
#include <FiniteStateMachine.h>
#include "TileComponent.h"
#include <InputManager.h>
#include "TeleportationPadComponent.h"
#include <algorithm>
#include "QbertCollisionComponent.h"
#include "QbertFSM.h"
#include <TextComponent.h>
#include "ScoreListenerComponent.h"
#include "LifeCounterComponent.h"
#include <SDLAudioSystem.h>
#include <AudioLocator.h>
#include "SlickSpawnerComponent.h"

Qbert_MainGame::Qbert_MainGame(const int level)
	: Integrian::App{ "Qbert_MainGame" + std::to_string(level) }
{
	m_Level = level;
}

void Qbert_MainGame::Start()
{
	using namespace Integrian;

	TextureManager::GetInstance().AddTexture("QbertHealth", "Resources/Images/UI/QbertHealth.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftBottomAnimation", "Resources/Images/Qbert/QbertLeftBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftTopAnimation", "Resources/Images/Qbert/QbertLeftTopAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightBottomAnimation", "Resources/Images/Qbert/QbertRightBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightTopAnimation", "Resources/Images/Qbert/QbertRightTopAnimation.png");

	SDLAudioSystem* pAudioSystem{ new SDLAudioSystem{} };
	pAudioSystem->AddSound("Resources/Sounds/Qbert_Jump.mp3");
	AudioLocator::Provide(pAudioSystem);

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(m_Level);
	pPyramidRoot->AddComponent(pTileFactoryComponent);
	AddGameObject("PyramidRoot", pPyramidRoot);

	GameObject* pQbert{ new GameObject{} };
	pQbert->AddComponent(new QbertFSM{ pQbert,
		std::array<Integrian::GameInput, 4>{GameInput{KeyboardInput::E}, GameInput{KeyboardInput::D},
		GameInput{KeyboardInput::A}, GameInput{KeyboardInput::Q}} });
	pQbert->AddComponent(new QbertSpriteComponent{ pQbert });
	pQbert->AddComponent(new QbertCollisionComponent{ pQbert });
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());
	AddGameObject("QbertOne", pQbert);

	GameObject* pScoreCounter{ new GameObject{} };
	pScoreCounter->AddComponent(new TextComponent{ pScoreCounter, "score: ", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} });
	pScoreCounter->AddComponent(new ScoreListenerComponent{ pScoreCounter });
	pScoreCounter->transform.SetPosition(Point2f{ 50.f, 400.f });
	AddGameObject("ScoreCounter", pScoreCounter);

	GameObject* pChangeToText{ new GameObject{} };
	pChangeToText->AddComponent(new TextComponent{ pChangeToText, "change to:", "Resources/Fonts/QbertFont.ttf", 15, RGBColour{255.f, 255.f, 0.f} });
	pChangeToText->transform.SetPosition(Point2f{ 50.f, 350.f });
	AddGameObject("ChangeToText", pChangeToText);

	GameObject* pChangeToTile{ new GameObject{} };
	pChangeToTile->AddComponent(new TextureComponent{ pChangeToTile,
		TextureManager::GetInstance().GetTexture("QbertLevel" + std::to_string(m_Level) + "ActiveTileTexture") });
	pChangeToTile->transform.SetPosition(Point2f{ 50.f, 300.f });
	AddGameObject("ChangeToTile", pChangeToTile);

	GameObject* pLifeCounter{ new GameObject{} };
	pLifeCounter->AddComponent(new LifeCounterComponent{ pLifeCounter });
	TextureComponent* pQbertLifeTexture{ new TextureComponent{ pLifeCounter, TextureManager::GetInstance().GetTexture("QbertHealth") } };
	pQbertLifeTexture->SetSourceRect(Rectf{ 0.f, 0.f, pQbertLifeTexture->GetTexture()->GetWidth(), pQbertLifeTexture->GetTexture()->GetHeight() / 3.f });
	pLifeCounter->AddComponent(pQbertLifeTexture);
	pLifeCounter->transform.SetPosition(Point2f{ 50.f, 250.f });
	AddGameObject("LifeCounter", pLifeCounter);

	GameObject* pSlickAndSamSpawner{ new GameObject{} };
	pSlickAndSamSpawner->AddComponent(new SlickSpawnerComponent{ pSlickAndSamSpawner });
	AddGameObject("SamAndSlickSpawner", pSlickAndSamSpawner);

	//pPyramidRoot->transform.SetScale(2.f, 2.f);
	//pQbert->transform.SetScale(2.f, 2.f);
}

void Qbert_MainGame::OnAppExit()
{
}

void Qbert_MainGame::Render() const
{
	using namespace Integrian;

	//for (GameObject* pTile : GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTiles())
	//{
	//	GameObject* pTest{ new GameObject{} };
	//	pTest->transform.SetPosition(pTile->GetComponentByType<TileComponent>()->GetCenter());
	//	pTest->AddComponent(new TextComponent{ pTest, std::to_string(pTile->GetComponentByType<TileComponent>()->GetIndex()), 10, RGBColour{255.f, 0.f, 0.f} });
	//	pTest->Render();
	//	SafeDelete(pTest);
	//}

	//DrawFilledCircle(Circlef{ Point2f{336.f - 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
	//DrawFilledCircle(Circlef{ Point2f{336.f + 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
}

void Qbert_MainGame::LateUpdate(const float)
{
}

const int Qbert_MainGame::GetLevel()
{
	return m_Level;
}

void Qbert_MainGame::SetLevel(const int level)
{
	m_Level = level;
}
