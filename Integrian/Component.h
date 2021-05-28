#pragma once
#ifndef INTEGRIAN_COMPONENT_H
#define INTEGRIAN_COMPONENT_H

#include "TypeDefines.h" // Point2f && Vector2f
#include "Structs.h" // Rectf, ...

namespace Integrian
{
	class GameObject;
	class Component abstract
	{
	public:
		Component(GameObject* pParent);
		virtual ~Component() = default;

		virtual void Initialize() {}
		virtual void PostInitialize() {}

		virtual void Update(const float) {}
		virtual void FixedUpdate(const float) {}
		virtual void LateUpdate(const float) {}
		
		virtual void Render(const Point2f&) const {}

		GameObject* m_pParent{};
	protected:

	private:
	};
}

#endif //!INTEGRIAN_COMPONENT_H