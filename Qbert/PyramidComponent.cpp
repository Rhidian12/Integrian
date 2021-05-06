#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pTiles{}
{
}

void PyramidComponent::Update(const float /*elapsedSeconds*/)
{
	if (!m_pTiles->empty())
	{
		std::cout << "UWU";
	}
}

std::vector<Integrian::GameObject*> PyramidComponent::CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	// we need to make a size x size triangle

	std::vector<GameObject*> gameObjects{};

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

			gameObjects.push_back(CreateTile(temp, pInactiveTileTexture));
		}
	}

	return gameObjects;
}

Integrian::GameObject* PyramidComponent::CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture)
{
	using namespace Integrian;

	GameObject* pTile{ new GameObject{} };

	pTile->AddComponent(new TextureComponent{ pTile, pInactiveTileTexture });
	pTile->transform.SetPosition(location);

	return pTile;
}
