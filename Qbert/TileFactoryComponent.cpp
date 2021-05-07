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

			pActiveApp->m_pGameObjects.insert(std::make_pair("Tile" + std::to_string(counter++), pTile));
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

	PyramidComponent* pPyramid{ m_pParent->GetComponentByType<PyramidComponent>() };

	const std::vector<GameObject*>* pTiles{ &pPyramid->GetTiles() };

	uint64_t counter{};
	for (unsigned int y{}; y < m_Size - 1; ++y)
	{
		for (unsigned int x{}; x <= y; ++x)
		{
			(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter + (y - x) + x + 1]->GetComponentByType<TileComponent>(), Direction::LeftBottom);
			(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter + (y - x) + x + 2]->GetComponentByType<TileComponent>(), Direction::RightBottom);

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

	std::vector<size_t> leftSide{};
	std::vector<size_t> rightSide{};

	size_t increment{ 2 };
	for (size_t i{}; i < pTiles->size();)
	{
		leftSide.push_back(i);

		if (i == 0)
			++i;
		else
			i += increment++;
	}

	increment = 2;
	for (size_t i{}; i < pTiles->size();)
	{
		rightSide.push_back(i);

		i += increment++;
	}

	for (int y{ int(m_Size) - 1 }; y >= 0; --y)
	{
		for (int x{ y }; x >= y; --x)
		{
			const std::vector<size_t>::const_iterator leftCIt{ std::find(leftSide.cbegin(), leftSide.cend(), counter) };
			const std::vector<size_t>::const_iterator rightCIt{ std::find(rightSide.cbegin(), rightSide.cend(), counter) };

			if (rightCIt == rightSide.cend() && leftCIt != leftSide.cend()) // the tile only has a left top connection
			{
				(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter - y]->GetComponentByType<TileComponent>(), Direction::RightTop);
			}
			else if (leftCIt == leftSide.cend() && rightCIt != rightSide.cend()) // the tile only has a right top connection
			{
				if (counter == 2)
					(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[0]->GetComponentByType<TileComponent>(), Direction::RightTop);
				else
					(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter - y - 1]->GetComponentByType<TileComponent>(), Direction::RightTop);
			}
			else // the tile has both a right top and left top connection
			{
				(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter - (int64_t(y) - x) - x + 1]->GetComponentByType<TileComponent>(), Direction::LeftTop);
				(*pTiles)[counter]->GetComponentByType<TileComponent>()->AddConnection((*pTiles)[counter - (int64_t(y) - x) - x + 2]->GetComponentByType<TileComponent>(), Direction::RightTop);
			}
			--counter;
		}
	}
}
