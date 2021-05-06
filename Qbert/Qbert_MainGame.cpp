#include "Qbert_MainGame.h"
#include <Texture.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include "PyramidComponent.h"
#include "TileFactoryComponent.h"

Qbert_MainGame::Qbert_MainGame()
	: Integrian::App{ "Qbert_MainGame" }
{
}

void Qbert_MainGame::Start()
{
	using namespace Integrian;

	TextureManager::GetInstance().AddTexture("QbertLevelOneInactiveTile", "Resources/Images/QbertLevelOneInactiveTile.png");
	TextureManager::GetInstance().AddTexture("QbertLevelOneActiveTile", "Resources/Images/QbertLevelOneActiveTile.png");
	TextureManager::GetInstance().AddTexture("QbertLeftBottomAnimation", "Resources/Images/Qbert/QbertLeftBottomAnimation.png");

	GameObject* pPyramidRoot{ new GameObject{} };
	pPyramidRoot->transform.SetPosition(Point2f{ m_WindowWidth / 2.f, (m_WindowHeight / 2.f) });

	PyramidComponent* pPyramidComponent{ new PyramidComponent{pPyramidRoot} };
	pPyramidRoot->AddComponent(pPyramidComponent);

	TileFactoryComponent* pTileFactoryComponent{ new TileFactoryComponent{pPyramidRoot} };
	pTileFactoryComponent->CreateTiles(7, TextureManager::GetInstance().GetTexture("QbertLevelOneInactiveTile"));
	pPyramidRoot->AddComponent(pTileFactoryComponent);

	GameObject* pQbert{ new GameObject{} };
	pQbert->AddComponent(new TextureComponent{ pQbert, TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation") });
	pQbert->transform.SetPosition(pPyramidComponent->GetTopTileCenter());

	m_pGameObjects.push_back(std::move(pPyramidRoot));
	m_pGameObjects.push_back(std::move(pQbert));
}

void Qbert_MainGame::Update(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Update(elapsedSeconds);
}

void Qbert_MainGame::FixedUpdate(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->FixedUpdate(elapsedSeconds);
}

void Qbert_MainGame::LateUpdate(const float elapsedSeconds)
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->LateUpdate(elapsedSeconds);
}

void Qbert_MainGame::Render() const
{
	for (Integrian::GameObject* pGameObject : m_pGameObjects)
		pGameObject->Render();
}
