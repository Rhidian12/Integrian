#include "TileComponent.h"
#include <GameObject.h>

TileComponent::TileComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Center{}
{
	m_Center = pParent->transform.GetPosition();
	m_Center.y += 16.f; // height offset
}

Integrian::Point2f TileComponent::GetCenter() const noexcept
{
	return m_Center;
}
