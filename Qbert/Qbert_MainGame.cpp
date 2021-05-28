#include "Qbert_MainGame.h"
#include <Texture.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include "PyramidComponent.h"
#include "QbertMovementComponent.h"
#include "TileFactoryComponent.h"
#include "QbertSpriteComponent.h"
#include <Utility Functions.h>

Qbert_MainGame::Qbert_MainGame()
	: Integrian::App{ "Qbert_MainGame" }
{
}

void Qbert_MainGame::Start()
{
	using namespace Integrian;

	//TextureManager::GetInstance().AddTexture("QbertLevelOneInactiveTile", "Resources/Images/QbertLevelOneInactiveTile.png");
	//TextureManager::GetInstance().AddTexture("QbertLevelOneActiveTile", "Resources/Images/QbertLevelOneActiveTile.png");

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(1);
	pPyramidRoot->AddComponent(pTileFactoryComponent);

	GameObject* pQbert{ new GameObject{} };
	//pQbert->AddComponent(new TextureComponent{ pQbert, TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation") });
	pQbert->AddComponent(new QbertMovementComponent{ pQbert });
	pQbert->AddComponent(new QbertSpriteComponent{ pQbert, "Resources/Images/Qbert/QbertLeftBottomAnimation.png" });
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());

	AddGameObject("PyramidRoot", pPyramidRoot);
	AddGameObject("Qbert", pQbert);
}

void Qbert_MainGame::Render() const
{
	Integrian::DrawRectangle(Integrian::Rectf{ 0.f, 0.f, 150.f, 150.f });
}
