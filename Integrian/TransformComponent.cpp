#include "IntegrianPCH.h" // precompiled header
#include "TransformComponent.h" // header

Integrian::TransformComponent::TransformComponent(GameObject* pParent)
	: TransformComponent{ pParent, {} }
{
}

Integrian::TransformComponent::TransformComponent(GameObject* pParent, const Point2f& position)
	: Component{ pParent }
	, m_Position{ position }
{
}

void Integrian::TransformComponent::SetPosition(const Point2f& position)
{
	m_Position = position;
}

const Integrian::Point2f& Integrian::TransformComponent::GetPosition() const
{
	return m_Position;
}
