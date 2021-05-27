#include "TileFactoryComponent.h"
#include <Texture.h>
#include <GameObject.h>
#include <TextureComponent.h>
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"

TileFactoryComponent::TileFactoryComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Size{}
{
}

void TileFactoryComponent::CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	m_Size = size;

	// we need to make a size x size triangle
	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ m_pParent->GetComponentByType<PyramidComponent>() };

	const Point2f& parentTransform{ m_pParent->transform.GetPosition() };
	const float textureWidth{ pInactiveTileTexture->GetWidth() };
	const float textureWidthDivTwo{ textureWidth * 0.5f };
	const float heightOffset{ 24.f }; // texture height offset since the devs of Qbert are evil

	uint64_t counter{};
	for (unsigned int y{}; y < size; ++y)
	{
		for (unsigned int x{}; x <= y; ++x)
		{
			Point2f temp{};

			if (x == 0)
				temp = Point2f{ parentTransform.x - y * textureWidthDivTwo, parentTransform.y - (y * heightOffset) };
			else
				temp = Point2f{ parentTransform.x - y * textureWidthDivTwo + (x * textureWidth), parentTransform.y - (y * heightOffset) };

			GameObject* pTile{ CreateTile(temp, pInactiveTileTexture) };

			pActiveApp->AddGameObject("Tile" + std::to_string(counter++), pTile);
			pPyramid->AddTile(pTile);
		}
	}

	FillConnections();
}

Integrian::GameObject* TileFactoryComponent::CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	GameObject* pTile{ new GameObject{} };

	pTile->transform.SetPosition(location);
	pTile->AddComponent(new TextureComponent{ pTile, pInactiveTileTexture });
	pTile->AddComponent(new TileComponent{ pTile });

	return pTile;
}

void TileFactoryComponent::FillConnections()
{
	using namespace Integrian;

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
