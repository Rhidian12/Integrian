#pragma once
#ifndef INTEGRIAN_TRANSFORMCOMPONENT_H
#define INTEGRIAN_TRANSFORMCOMPONENT_H

#include "Component.h"
#include "Structs.h"

namespace Integrian
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent();
		TransformComponent(const Point2f& position);
		~TransformComponent() = default;

		void SetPosition(const Point2f& position);
		const Point2f& GetPosition() const;

	private:
		Point2f m_Position;
	};
};

#endif // INTEGRIAN_TRANSFORMCOMPONENT_H