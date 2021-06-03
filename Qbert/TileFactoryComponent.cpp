#include "TileFactoryComponent.h"
#include <Texture.h>
#include <GameObject.h>
#include <TextureComponent.h>
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"
#include <fstream>
#include <TextureManager.h>
#include <iostream>
#include <iomanip>
#include "TeleportationPadComponent.h"
#include <AnimationComponent.h>
#include "BallSpawnerComponent.h"
#include <FiniteStateMachine.h>
#include <Blackboard.h>
#include <memory>
#include "TileFSM.h"
#include "CoilyFSM.h"
#include "QbertGraphComponent.h"

TileFactoryComponent::TileFactoryComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Size{}
	, m_Level{}
{
}

void TileFactoryComponent::CreateTiles(const int level)
{
	using namespace Integrian;
	using json = nlohmann::json;

	json levelFormat{ ReadFile(level) };

	m_Size = *levelFormat.find("Size");
	m_Level = level;

	const std::string inactiveTextureName{ *levelFormat.find("TileTexture") };
	const size_t locationOfI{ inactiveTextureName.find_first_of('I') };
	std::string activeTextureName{ inactiveTextureName.substr(0, locationOfI) };
	activeTextureName += inactiveTextureName.substr(locationOfI + 2, inactiveTextureName.size() - locationOfI - 2); // +- 2 because we need to get rid of "In"
	activeTextureName[activeTextureName.find_first_of('a')] = 'A';

	TextureManager& textureManager{ TextureManager::GetInstance() };

	textureManager.AddTexture("QbertLevel" + std::to_string(level) + "InactiveTileTexture",
		"Resources/Images/Tiles/" + inactiveTextureName);
	//textureManager.AddTexture("QbertLevel" + std::to_string(level) + "ActiveTileTexture",
	//	"Resources/Images/Tiles/" + activeTextureName);
	textureManager.AddTexture("Level" + std::to_string(level) + "TPPad",
		"Resources/Images/TP Pads/" + std::string{ *levelFormat.find("TeleportationPadTexture") });

	Texture* pInactiveTileTexture{ TextureManager::GetInstance().GetTexture("QbertLevel" + std::to_string(level) + "InactiveTileTexture") };

	// we need to make a size x size triangle
	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ m_pParent->GetComponentByType<PyramidComponent>() };

	const Point2f& parentTransform{ m_pParent->transform.GetPosition() };
	const float textureWidth{ pInactiveTileTexture->GetWidth() };
	const float textureWidthDivTwo{ textureWidth * 0.5f };
	const float heightOffset{ 24.f }; // texture height offset since the devs of Qbert are evil

	uint32_t counter{};
	for (unsigned int y{}; y < m_Size; ++y)
	{
		for (unsigned int x{}; x <= y; ++x)
		{
			Point2f temp{};

			if (x == 0)
				temp = Point2f{ parentTransform.x - y * textureWidthDivTwo, parentTransform.y - (y * heightOffset) };
			else
				temp = Point2f{ parentTransform.x - y * textureWidthDivTwo + (x * textureWidth), parentTransform.y - (y * heightOffset) };

			GameObject* pTile{ CreateTile(temp, pInactiveTileTexture, counter) };

			pActiveApp->AddGameObject("Tile" + std::to_string(counter++), pTile);
			pPyramid->AddTile(pTile);
		}
	}

	json tpLocations = *levelFormat.find("TeleportLocations");
	unsigned int amountOfRedBalls = *levelFormat.find("Red Balls");

	CreateTeleportationPads(level, tpLocations);
	FillConnections(tpLocations);
	CreateRedBallSpawner(amountOfRedBalls);
	CreateTileFSM(*levelFormat.find("TileFSM"));
	CreateEnemies(*levelFormat.find("Enemies"));
	CreateGraph();
}

const unsigned int TileFactoryComponent::GetSize() const noexcept
{
	return m_Size;
}

Integrian::GameObject* TileFactoryComponent::CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture, const unsigned int index)
{
	using namespace Integrian;

	GameObject* pTile{ new GameObject{} };

	pTile->transform.SetPosition(location);
	pTile->AddComponent(new TextureComponent{ pTile, pInactiveTileTexture });
	pTile->AddComponent(new TileComponent{ pTile, index });

	return pTile;
}

void TileFactoryComponent::FillConnections(nlohmann::json teleporterLocations) const
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	const std::vector<GameObject*>* pTiles{ &m_pParent->GetComponentByType<PyramidComponent>()->GetTiles() };

	uint64_t counter{};
	for (unsigned int y{}; y < m_Size - 1; ++y)
	{
		for (unsigned int x{}; x <= y; ++x)
		{
			const uint64_t leftBottomIndex{ counter + (y - x) + x + 1 };
			const uint64_t rightBottomIndex{ counter + (y - x) + x + 2 };
			(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[leftBottomIndex]->GetComponentByType<TileComponent>(), Direction::LeftBottom);
			(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[rightBottomIndex]->GetComponentByType<TileComponent>(), Direction::RightBottom);

			(*pTiles)[leftBottomIndex]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter]->GetComponentByType<TileComponent>(), Direction::RightTop);
			(*pTiles)[rightBottomIndex]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter]->GetComponentByType<TileComponent>(), Direction::LeftTop);

			for (const nlohmann::json& element : teleporterLocations)
			{
				if (*element.find("isLeft") && y == *element.find("row"))
					if (x == 0)
						(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection(pActiveApp->GetGameObject("TeleportationPad0")->GetComponentByType<TeleportationPadComponent>(), Direction::LeftTop);

				if (!(*element.find("isLeft")) && y == *element.find("row"))
					if (x == y)
						(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection(pActiveApp->GetGameObject("TeleportationPad1")->GetComponentByType<TeleportationPadComponent>(), Direction::RightTop);
			}

			++counter;
		}
	}

	// y == 0  	      0
	// y == 1  	     1 2
	// y == 2  	    3 4 5
	// y == 3      6 7 8 9
	// y == 4   10 11 12 13 14
	// y == 5  15 16 17 18 19 20
	// y == 6 21 22 23 24 25 26 27

	// left side : 0 | 1 | 3 | 6 | 10 | 15 | 21
	// right side: 0 | 2 | 5 | 9 | 14 | 20 | 27
}

void TileFactoryComponent::CreateTeleportationPads(const int level, nlohmann::json teleporterLocations) const
{
	using namespace Integrian;

	const std::vector<GameObject*>* pTiles{ &m_pParent->GetComponentByType<PyramidComponent>()->GetTiles() };

	float xCoordinate{ std::numeric_limits<float>::max() };

	for (GameObject* pTile : (*pTiles))
		if (pTile->transform.GetPosition().x < xCoordinate)
			xCoordinate = pTile->transform.GetPosition().x;

	Texture* pTpPadTexture{ TextureManager::GetInstance().GetTexture("Level" + std::to_string(level) + "TPPad") };
	const float tpPadWidth{ pTpPadTexture->GetWidth() * 0.25f };
	const Point2f& center{ (*pTiles)[0]->GetComponentByType<TileComponent>()->GetCenter() };

	float xDifference{ center.x - xCoordinate - tpPadWidth * 1.5f };
	const float tileHeight{ (*pTiles)[0]->GetComponentByType<TextureComponent>()->GetTexture()->GetHeight() };

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	int counter{};
	for (int i{ -1 }; i < 2; i += 2)
	{
		GameObject* pTpPad{ new GameObject{} };
		pTpPad->transform.SetPosition(Point2f{ center.x + i * xDifference - tpPadWidth * 0.5f, center.y - (tileHeight * 0.5f) * ((*teleporterLocations[counter].find("row")) + 1) });
		pTpPad->AddComponent(new TeleportationPadComponent{ pTpPad });
		pTpPad->AddComponent(new AnimationComponent{ pTpPad, 4, 8, pTpPadTexture });
		pActiveApp->AddGameObject("TeleportationPad" + std::to_string(counter++), pTpPad);
	}
}

void TileFactoryComponent::CreateRedBallSpawner(const unsigned int amountOfRedBalls) const
{
	using namespace Integrian;

	GameObject* const pSpawner{ new GameObject{} };
	pSpawner->AddComponent(new BallSpawnerComponent{ pSpawner, amountOfRedBalls });

	App* const pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	pActiveApp->AddGameObject("BallSpawner", pSpawner);
}

void TileFactoryComponent::CreateTileFSM(nlohmann::json tileFSM) const
{
	using namespace Integrian;

	std::vector<std::shared_ptr<FSMState>> states;

	GameObject* pTileFSM{ new GameObject{} };
	TextureManager& textureManager{ TextureManager::GetInstance() };
	App* const pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	Texture* pInactiveTileTexture{ textureManager.GetTexture("QbertLevel" + std::to_string(m_Level) + "InactiveTileTexture") };

	for (const nlohmann::json& element : *tileFSM.find("TileTextures"))
	{
		const auto it{ element.find("ActiveTexture") };
		textureManager.AddTexture("QbertLevel" + std::to_string(m_Level) + "ActiveTileTexture", "Resources/Images/Tiles/" + std::string{ *it });
	}

	Texture* pActiveTileTexture{ textureManager.GetTexture("QbertLevel" + std::to_string(m_Level) + "ActiveTileTexture") };

	switch (static_cast<TileChange>(*tileFSM.find("TileChange")))
	{
	case TileChange::Permanent: // Just switches colour permanently
	{
		TileFSM* pTileFSMComponent{ new TileFSM{pTileFSM} };
		pTileFSM->AddComponent(pTileFSMComponent);
		pTileFSM->AddComponent(pTileFSMComponent->CreatePermanentFSM(pInactiveTileTexture, pActiveTileTexture));
		pActiveApp->AddGameObject("TileFSM", pTileFSM);
	}
	break;
	//case 1:
	//	break;
	}
}

void TileFactoryComponent::CreateEnemies(nlohmann::json enemies) const
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	TextureManager& textureManager{ TextureManager::GetInstance() };
	textureManager.AddTexture("CoilyBall", "Resources/Images/Coily/Coily_Ball.png");
	textureManager.AddTexture("CoilyLeftBottomAnimation", "Resources/Images/Coily/CoilyLeftBottomAnimation.png");
	textureManager.AddTexture("CoilyRightBottomAnimation", "Resources/Images/Coily/CoilyRightBottomAnimation.png");
	textureManager.AddTexture("CoilyLeftTopAnimation", "Resources/Images/Coily/CoilyLeftTopAnimation.png");
	textureManager.AddTexture("CoilyRightTopAnimation", "Resources/Images/Coily/CoilyRightTopAnimation.png");

	int counter{};
	for (const nlohmann::json& element : enemies)
	{
		GameObject* pEnemy{ new GameObject{} };
		pEnemy->SetTag("Purple");

		const std::string enemyName{ *element.find("Enemy") };

		if (enemyName == "Coily")
		{
			TextureComponent* pTexture{ new TextureComponent{ pEnemy, textureManager.GetTexture("CoilyBall") } };
			pTexture->SetSourceRect(Rectf{ 0.f, 0.f, pTexture->GetTexture()->GetWidth() / 2.f, pTexture->GetTexture()->GetHeight() });
			pEnemy->AddComponent(pTexture);
			pEnemy->AddComponent(new CoilyFSM{ pEnemy });
		}

		pActiveApp->AddGameObject("Enemy" + std::to_string(counter++), pEnemy);
	}
}

void TileFactoryComponent::CreateGraph() const
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	GameObject* pGraph{ new GameObject{} };
	pGraph->AddComponent(new QbertGraphComponent{ pGraph });
	pActiveApp->AddGameObject("QbertGraph", pGraph);
}

nlohmann::json TileFactoryComponent::ReadFile(const int level)
{
	std::ifstream input{};
	input.open("Resources/Levels/Level" + std::to_string(level) + ".json");

	nlohmann::json json{};

	if (input.is_open())
		input >> json;

	input.close();

	return json;
}
