#pragma once
#ifndef INTEGRIAN_TRANSFORMCOMPONENT_H
#define INTEGRIAN_TRANSFORMCOMPONENT_H

#include "Component.h" // Component

namespace Integrian
{
	class GameObject;
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pParent);
		TransformComponent(GameObject* pParent, const Point2f& position);
		~TransformComponent() = default;

		void SetPosition(const Point2f& position);
		[[nodiscard]] const Point2f& GetPosition() const;

	private:
		Point2f m_Position;
	};
};

#endif // INTEGRIAN_TRANSFORMCOMPONENT_H