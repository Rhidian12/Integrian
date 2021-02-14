#include "TransformComponent.h"

Integrian::TransformComponent::TransformComponent()
	: TransformComponent{ {} }
{
}

Integrian::TransformComponent::TransformComponent(const Point2f& position)
	: m_Position{ position }
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
