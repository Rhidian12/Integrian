#include "TileComponent.h"
#include <GameObject.h>
#include <assert.h>

TileComponent::TileComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Center{}
	, m_ActiveConnections{}
	, m_pConnections{}
{
	m_Center = pParent->transform.GetPosition();
	m_Center.y += 24.f; // height offset
	m_Center.x += 16.f; // width offset
}

Integrian::Point2f TileComponent::GetCenter() const noexcept
{
	return m_Center;
}

void TileComponent::AddConnection(TileComponent* pTile, const Direction direction)
{
	assert(m_ActiveConnections < 4);
	m_pConnections[static_cast<std::underlying_type_t<Direction>>(direction)] = pTile;

	if(pTile)
		m_ActiveConnections++;
}

void TileComponent::AddConnection(TeleportationPadComponent* pTpPad, const Direction direction)
{
	assert(m_ActiveConnections < 4);
	m_pConnections[static_cast<std::underlying_type_t<Direction>>(direction)] = pTpPad;

	if (pTpPad)
		m_ActiveConnections++;
}

const std::array<Connection, 4>& TileComponent::GetConnections() const noexcept
{
	return m_pConnections;
}
