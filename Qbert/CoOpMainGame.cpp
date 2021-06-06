#include "CoOpMainGame.h"

#include <TextureManager.h>
#include <Texture.h>
#include <TextureComponent.h>
#include <TextComponent.h>

#include "PyramidComponent.h"
#include "TileFactoryComponent.h"
#include "QbertFSM.h"
#include "Qbert_MainGame.h"
#include "QbertCollisionComponent.h"
#include "QbertSpriteComponent.h"
#include "ScoreListenerComponent.h"
#include "LifeCounterComponent.h"
#include "Qbert_MainGame.h"
#include "TileComponent.h"

CoOpMainGame::CoOpMainGame()
	: App{ "CoOpMainGame" + std::to_string(Qbert_MainGame::GetLevel()) }
{
}

void CoOpMainGame::Start()
{
	using namespace Integrian;

	TextureManager::GetInstance().AddTexture("QbertHealth", "Resources/Images/UI/QbertHealth.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftBottomAnimation", "Resources/Images/Qbert/QbertLeftBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertLeftTopAnimation", "Resources/Images/Qbert/QbertLeftTopAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightBottomAnimation", "Resources/Images/Qbert/QbertRightBottomAnimation.png");
	Integrian::TextureManager::GetInstance().AddTexture("QbertRightTopAnimation", "Resources/Images/Qbert/QbertRightTopAnimation.png");

	SetClearColour(RGBColour{ 49.f, 34.f, 119.f });

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(Qbert_MainGame::GetLevel());
	pPyramidRoot->AddComponent(pTileFactoryComponent);
	AddGameObject("PyramidRoot", pPyramidRoot);

	const std::vector<GameObject*>* const pTiles{ &pPyramidComponent->GetTiles() };
	Point2f mostLeftTile{ (*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter() };
	Point2f mostRightTile{ (*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter() };

	for (GameObject* pTile : *pTiles)
	{
		if (pTile->GetComponentByType<TileComponent>()->GetCenter().x < mostLeftTile.x)
		{
			mostLeftTile = pTile->GetComponentByType<TileComponent>()->GetCenter();
		}

		if (pTile->GetComponentByType<TileComponent>()->GetCenter().x > mostRightTile.x)
		{
			mostRightTile = pTile->GetComponentByType<TileComponent>()->GetCenter();
		}
	}


	GameObject* pQbertOne{ new GameObject{} };
	pQbertOne->AddComponent(new QbertFSM{ pQbertOne,
		std::array<Integrian::GameInput, 4>{GameInput{KeyboardInput::E}, GameInput{KeyboardInput::D},
		GameInput{KeyboardInput::A}, GameInput{KeyboardInput::Q}} });
	pQbertOne->AddComponent(new QbertSpriteComponent{ pQbertOne });
	pQbertOne->AddComponent(new QbertCollisionComponent{ pQbertOne });
	pQbertOne->transform.SetPosition(mostLeftTile);
	AddGameObject("QbertOne", pQbertOne);

	GameObject* pQbertTwo{ new GameObject{} };
	pQbertTwo->AddComponent(new QbertFSM{ pQbertTwo,
		std::array<Integrian::GameInput, 4>{GameInput{ControllerInput::ButtonB}, GameInput{ControllerInput::ButtonA},
		GameInput{ControllerInput::ButtonX}, GameInput{ControllerInput::ButtonY}} });
	pQbertTwo->AddComponent(new QbertSpriteComponent{ pQbertTwo });
	pQbertTwo->AddComponent(new QbertCollisionComponent{ pQbertTwo });
	pQbertTwo->transform.SetPosition(mostRightTile);
	AddGameObject("QbertTwo", pQbertTwo);

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
		TextureManager::GetInstance().GetTexture("QbertLevel" + std::to_string(Qbert_MainGame::GetLevel()) + "ActiveTileTexture") });
	pChangeToTile->transform.SetPosition(Point2f{ 50.f, 300.f });
	AddGameObject("ChangeToTile", pChangeToTile);

	GameObject* pLifeCounter{ new GameObject{} };
	pLifeCounter->AddComponent(new LifeCounterComponent{ pLifeCounter });
	TextureComponent* pQbertLifeTexture{ new TextureComponent{ pLifeCounter, TextureManager::GetInstance().GetTexture("QbertHealth") } };
	pQbertLifeTexture->SetSourceRect(Rectf{ 0.f, 0.f, pQbertLifeTexture->GetTexture()->GetWidth(), pQbertLifeTexture->GetTexture()->GetHeight() / 3.f });
	pLifeCounter->AddComponent(pQbertLifeTexture);
	pLifeCounter->transform.SetPosition(Point2f{ 50.f, 250.f });
	AddGameObject("LifeCounter", pLifeCounter);

	//pPyramidRoot->transform.SetScale(2.f, 2.f);
	//pQbert->transform.SetScale(2.f, 2.f);
}
