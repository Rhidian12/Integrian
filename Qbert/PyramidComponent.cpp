#include "PyramidComponent.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TextureManager.h>
#include <Texture.h>
#include <algorithm>
#include "TileComponent.h"

PyramidComponent::PyramidComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pTiles{}
{
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
	auto it = std::max_element(m_pTiles.begin(), m_pTiles.end(), [this](Integrian::GameObject* pA, Integrian::GameObject* pB)->bool
		{
			return pA->transform.GetPosition().y < pB->transform.GetPosition().y;
		});

	return (*it)->GetComponentByType<TileComponent>()->GetCenter();
}
