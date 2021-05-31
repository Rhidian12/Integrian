#pragma once
#ifndef INTEGRIAN_TRANSFORMCOMPONENT_H
#define INTEGRIAN_TRANSFORMCOMPONENT_H

#include "Component.h" // Component
#include "Shape.h" // Shape

namespace Integrian
{
	class GameObject;
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pParent);
		~TransformComponent() = default;

		virtual void FixedUpdate(const float) override;

		void SetPosition(const Point2f& position)		noexcept;
		void SetScale(const float x, const float y)		noexcept;
		void SetScale(const Point2f& scale)				noexcept;
		void SetRotation(const float angle)				noexcept;
		void SetShape(const TypeOfShape typeOfShape)	noexcept;
		void SetDestRectWidth(const float width)		noexcept;
		void SetDestRectHeight(const float height)		noexcept;
		void SetDestRectDimensions(const float width, const float height)	noexcept;

		[[nodiscard]] const Point2f& GetPosition()	const noexcept;
		[[nodiscard]] const Point2f& GetScale()		const noexcept;
		[[nodiscard]] const float GetRotation()		const noexcept;
		[[nodiscard]] const Rectf& GetDestRect()	const noexcept;

		void Translate(const Vector2f& velocity) noexcept;
		void Rotate(const float angleInRadians) noexcept;

	private:
		enum class TransformChanged : uint8_t
		{
			None = 0x00,
			Translation = 0x01,
			Rotation = 0x02,
			Scale = 0x04
		};

		Point2f&& RotatePoint(const Point2f& point);

		Vector2f m_Translation;
		Point2f m_Scale;
		float m_Angle; // in radians!
		Shape m_Shape;
		Rectf m_DestRect;
		Rectf m_SourceRect;
		TransformChanged m_TransformChanged;
	};
};

#endif // INTEGRIAN_TRANSFORMCOMPONENT_H