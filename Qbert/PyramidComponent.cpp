#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <algorithm>
#include "TileComponent.h"
#include <Utility Functions.h>

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pTiles{}
{
}

void PyramidComponent::Render(const Integrian::Point2f&) const
{
	using namespace Integrian;

	//for (GameObject* pTile : m_pTiles)
	//{
	//	//if (pTile->GetComponentByType<TileComponent>()->GetConnections()[3] != nullptr)
	//	//{
	//	//	DrawLine(pTile->GetComponentByType<TileComponent>()->GetCenter(), pTile->GetComponentByType<TileComponent>()->GetConnections()[3]->GetCenter(), RGBColour{ 255.f, 0.f, 0.f });
	//	//}
	//
	//	//if (pTile->GetComponentByType<TileComponent>()->GetConnections()[static_cast<uint8_t>(Direction::RightTop)] != nullptr)
	//	//{
	//	//	DrawLine(pTile->GetComponentByType<TileComponent>()->GetCenter(), pTile->GetComponentByType<TileComponent>()->GetConnections()[static_cast<uint8_t>(Direction::RightTop)]->GetCenter(), RGBColour{ 255.f, 0.f, 0.f });
	//	//}
	//}
}

void PyramidComponent::Update(const float /*elapsedSeconds*/)
{
}

void PyramidComponent::AddTile(Integrian::GameObject* pTile)
{
	m_pTiles.push_back(pTile);
}

Integrian::Point2f PyramidComponent::GetTopTileCenter() const noexcept
{
	return m_pTiles[0]->GetComponentByType<TileComponent>()->GetCenter();
}

TileComponent* PyramidComponent::GetTile(const Integrian::Point2f& location) const
{
	using namespace Integrian;

	const std::vector<GameObject*>::const_iterator cIt{ std::find_if(m_pTiles.cbegin(), m_pTiles.cend(), [location](GameObject* pTile)
		{
			return pTile->GetComponentByType<TileComponent>()->GetCenter() == location;
		}) };

	if (cIt != m_pTiles.cend())
		return (*cIt)->GetComponentByType<TileComponent>();
	else
	{
		Logger::LogWarning("PyramidComponent::GetTile returned a nullptr\n");
		return nullptr;
	}
}

const std::vector<Integrian::GameObject*>& PyramidComponent::GetTiles() const noexcept
{
	return m_pTiles;
}
