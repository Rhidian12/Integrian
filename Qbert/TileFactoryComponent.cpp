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
{
}

void TileFactoryComponent::CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	// we need to make a size x size triangle
	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	PyramidComponent* pPyramid{ m_pParent->GetComponentByType<PyramidComponent>() };

	const Point2f& parentTransform{ m_pParent->transform.GetPosition() };
	const float textureWidth{ pInactiveTileTexture->GetWidth() };
	const float textureWidthDivTwo{ textureWidth * 0.5f };
	const float heightOffset{ 24.f }; // texture height offset since the devs of Qbert are evil

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

			pActiveApp->m_pGameObjects.push_back(pTile);
			pPyramid->AddTile(pTile);
		}
	}
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
