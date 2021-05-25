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
	//uint64_t counter{};
	//for (unsigned int y{}; y < 6; ++y)
	//{
	//	for (unsigned int x{}; x <= y; ++x)
	//	{
	//		Integrian::DrawLine(m_pTiles[counter]->GetComponentByType<TileComponent>()->GetCenter(), m_pTiles[counter + (y - x) + x + 1]->GetComponentByType<TileComponent>()->GetCenter(), Integrian::RGBColour{ 255.f, 0.f,0.f });
	//		Integrian::DrawLine(m_pTiles[counter]->GetComponentByType<TileComponent>()->GetCenter(), m_pTiles[counter + (y - x) + x + 2]->GetComponentByType<TileComponent>()->GetCenter(), Integrian::RGBColour{ 255.f, 0.f,0.f });
	//
	//		++counter;
	//	}
	//}
	//std::vector<size_t> leftSide{};
	//std::vector<size_t> rightSide{};
	//
	//size_t increment{ 2 };
	//for (size_t i{}; i < m_pTiles.size();)
	//{
	//	leftSide.push_back(i);
	//
	//	if (i == 0)
	//		++i;
	//	else
	//		i += increment++;
	//}
	//
	//increment = 2;
	//for (size_t i{}; i < m_pTiles.size();)
	//{
	//	rightSide.push_back(i);
	//
	//	i += increment++;
	//}
	//
	//for (int y{ int(7) - 1 }; y >= 0; --y)
	//{
	//	for (int x{ y }; x >= 0; --x)
	//	{
	//		const std::vector<size_t>::const_iterator leftCIt{ std::find(leftSide.cbegin(), leftSide.cend(), counter) };
	//		const std::vector<size_t>::const_iterator rightCIt{ std::find(rightSide.cbegin(), rightSide.cend(), counter) };
	//
	//		if(leftCIt != leftSide.cend() && rightCIt != rightSide.cend()) // the tile has both a right top and left top connection
	//		{
	//			Integrian::DrawLine(m_pTiles[counter]->GetComponentByType<TileComponent>()->GetCenter(), m_pTiles[counter - (int64_t(y) - x) - x + 1]->GetComponentByType<TileComponent>()->GetCenter(), Integrian::RGBColour{ 255.f, 0.f, 0.f });
	//			Integrian::DrawLine(m_pTiles[counter]->GetComponentByType<TileComponent>()->GetCenter(), m_pTiles[counter - (int64_t(y) - x) - x + 2]->GetComponentByType<TileComponent>()->GetCenter(), Integrian::RGBColour{ 255.f, 0.f, 0.f });
	//		}
	//	}
	//}
	//Integrian::DrawFilledCircle(Integrian::Circlef{m_pTiles[i]->GetComponentByType<TileComponent>()->GetCenter(), 3.f}, Integrian::RGBColour{ 255.f,0.f,0.f });
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
