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

Qbert_MainGame::Qbert_MainGame()
	: Integrian::App{ "Qbert_MainGame" }
{
}

void Qbert_MainGame::Start()
{
	using namespace Integrian;

	TextureManager::GetInstance().AddTexture("QbertHealth", "Resources/Images/UI/QbertHealth.png");

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(1);
	pPyramidRoot->AddComponent(pTileFactoryComponent);
	AddGameObject("PyramidRoot", pPyramidRoot);

	GameObject* pQbert{ new GameObject{} };
	pQbert->AddComponent(new QbertFSM{ pQbert });
	pQbert->AddComponent(new QbertSpriteComponent{ pQbert });
	pQbert->AddComponent(new QbertCollisionComponent{ pQbert });
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());
	AddGameObject("Qbert", pQbert);

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
		TextureManager::GetInstance().GetTexture("QbertLevel" + std::to_string(pTileFactoryComponent->GetLevel()) + "ActiveTileTexture") });
	pChangeToTile->transform.SetPosition(Point2f{ 50.f, 300.f });
	AddGameObject("ChangeToTile", pChangeToTile);

	GameObject* pLifeCounter{ new GameObject{} };
	pLifeCounter->AddComponent(new LifeCounterComponent{ pLifeCounter });
	TextureComponent* pQbertLifeTexture{ new TextureComponent{ pLifeCounter, TextureManager::GetInstance().GetTexture("QbertHealth") } };
	pQbertLifeTexture->SetSourceRect(Rectf{0.f, 0.f, pQbertLifeTexture->GetTexture()->GetWidth(), pQbertLifeTexture->GetTexture()->GetHeight() / 3.f });
	pLifeCounter->AddComponent(pQbertLifeTexture);
	pLifeCounter->transform.SetPosition(Point2f{ 50.f, 250.f });
	AddGameObject("LifeCounter", pLifeCounter);

	//pPyramidRoot->transform.SetScale(2.f, 2.f);
	//pQbert->transform.SetScale(2.f, 2.f);
}

void Qbert_MainGame::OnAppExit()
{
}

void Qbert_MainGame::Render() const
{
	using namespace Integrian;

	for (GameObject* pTile : GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>()->GetTiles())
	{
		GameObject* pTest{ new GameObject{} };
		pTest->transform.SetPosition(pTile->GetComponentByType<TileComponent>()->GetCenter());
		pTest->AddComponent(new TextComponent{ pTest, std::to_string(pTile->GetComponentByType<TileComponent>()->GetIndex()), 10, RGBColour{255.f, 0.f, 0.f} });
		pTest->Render();
		SafeDelete(pTest);
	}

	//DrawFilledCircle(Circlef{ Point2f{336.f - 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
	//DrawFilledCircle(Circlef{ Point2f{336.f + 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
}

void Qbert_MainGame::LateUpdate(const float)
{
}