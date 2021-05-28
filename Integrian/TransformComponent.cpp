#include "IntegrianPCH.h" // precompiled header
#include "TransformComponent.h" // header
#include "Timer.h"

Integrian::TransformComponent::TransformComponent(GameObject* pParent)
	: Component{ pParent }
	, m_Scale{ 1.f, 1.f }
	, m_Angle{}
	, m_Shape{ TypeOfShape::Rectangle }
	, m_TransformChanged{}
	, m_Translation{}
{
}

void Integrian::TransformComponent::FixedUpdate(const float)
{
	using UnderlyingType = std::underlying_type_t<TransformChanged>;

	if (m_Scale.x != 1.f)
		std::cout << "uwu";

	if (static_cast<UnderlyingType>(m_TransformChanged))
	{
		// set translation matrix
		Matrix3f translationMatrix{ Matrix3f::GetIdentity() };
		translationMatrix[0].z = m_Translation.x;
		translationMatrix[1].z = m_Translation.y;

		// set scale matrix
		Matrix3f scaleMatrix{ Matrix3f::GetIdentity() };
		scaleMatrix[0].x = m_Scale.x;
		scaleMatrix[1].y = m_Scale.y;

		// calculate rotation matrix
		Matrix3f rotationMatrix{ Matrix3f::GetIdentity() };
		rotationMatrix[0].x = cos(m_Angle);
		rotationMatrix[0].y = -sin(m_Angle);
		rotationMatrix[1].x = sin(m_Angle);
		rotationMatrix[1].y = cos(m_Angle);

		const Matrix3f transformationMatrix{ translationMatrix * rotationMatrix * scaleMatrix };

		m_DestRect[VertexLocation::LeftBottom]	= Point2f{ (transformationMatrix * m_DestRect[VertexLocation::LeftBottom])	};
		m_DestRect[VertexLocation::LeftTop]		= Point2f{ (transformationMatrix * m_DestRect[VertexLocation::LeftTop])		};
		m_DestRect[VertexLocation::RightBottom] = Point2f{ (transformationMatrix * m_DestRect[VertexLocation::RightBottom])	};
		m_DestRect[VertexLocation::RightTop]	= Point2f{ (transformationMatrix * m_DestRect[VertexLocation::RightTop])	};

		m_Translation = {};
	}

	m_TransformChanged = TransformChanged::None;
}

void Integrian::TransformComponent::SetPosition(const Point2f& position) noexcept
{
	//m_Translation = position - m_DestRect[VertexLocation::LeftBottom];
	m_DestRect[VertexLocation::LeftBottom] = position;

	//m_TransformChanged = TransformChanged::Translation;
}

void Integrian::TransformComponent::SetScale(const float x, const float y) noexcept
{
	m_Scale = Point2f{ x, y };

	m_TransformChanged = TransformChanged::Scale;
}

void Integrian::TransformComponent::SetScale(const Point2f& scale) noexcept
{
	m_Scale = scale;

	m_TransformChanged = TransformChanged::Scale;
}

void Integrian::TransformComponent::SetRotation(const float angle) noexcept
{
	m_Angle = angle;

	m_TransformChanged = TransformChanged::Rotation;
}

void Integrian::TransformComponent::SetShape(const TypeOfShape typeOfShape) noexcept
{
	m_Shape.SetShape(typeOfShape);
}

void Integrian::TransformComponent::SetDestRectWidth(const float width) noexcept
{
	m_DestRect.width = width;
}

void Integrian::TransformComponent::SetDestRectHeight(const float height) noexcept
{
	m_DestRect.height = height;
}

void Integrian::TransformComponent::SetDestRectDimensions(const float width, const float height) noexcept
{
	m_DestRect.width = width;
	m_DestRect.height = height;
}

const Integrian::Point2f& Integrian::TransformComponent::GetPosition() const noexcept
{
	return m_DestRect[VertexLocation::LeftBottom];
}

const Integrian::Point2f& Integrian::TransformComponent::GetScale() const noexcept
{
	return m_Scale;
}

const float Integrian::TransformComponent::GetRotation() const noexcept
{
	return m_Angle;
}

const Integrian::Rectf& Integrian::TransformComponent::GetDestRect() const noexcept
{
	return m_DestRect;
}

void Integrian::TransformComponent::Translate(const Vector2f& velocity) noexcept
{
	m_Translation = velocity * Timer::GetInstance().GetElapsedSeconds();

	m_TransformChanged = TransformChanged::Translation;
}

void Integrian::TransformComponent::Rotate(const float angleInRadians) noexcept
{
	m_Angle += angleInRadians * Timer::GetInstance().GetElapsedSeconds();

	m_TransformChanged = TransformChanged::Rotation;
}

Integrian::Point2f&& Integrian::TransformComponent::RotatePoint(const Point2f& point)
{
	Point2f tempPoint
	{
		point.x * cos(m_Angle) - point.y * sin(m_Angle), // 'x = x * cos(angle) - y * sin(angle)
		point.x * sin(m_Angle) + point.y * cos(m_Angle) // 'y = x * sin(angle) + y * cos(angle)
	};

	return std::move(tempPoint);
}
