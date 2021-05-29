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

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(1);
	pPyramidRoot->AddComponent(pTileFactoryComponent);

	GameObject* pQbert{ new GameObject{} };
	pQbert->AddComponent(new QbertMovementComponent{ pQbert });
	pQbert->AddComponent(new QbertSpriteComponent{ pQbert });
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());

	AddGameObject("PyramidRoot", pPyramidRoot);
	AddGameObject("Qbert", pQbert);

	//pPyramidRoot->transform.SetScale(2.f, 2.f);
	//pQbert->transform.SetScale(2.f, 2.f);
}

void Qbert_MainGame::Render() const
{
	using namespace Integrian;

	//DrawFilledCircle(Circlef{ Point2f{336.f - 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
	//DrawFilledCircle(Circlef{ Point2f{336.f + 112.f, 174.f}, 3.f }, RGBColour{ 255.f, 0.f, 0.f });
}
