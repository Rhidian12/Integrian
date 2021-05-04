#pragma once

#ifndef INTEGRIAN_FPSCOMPONENT_H
#define INTEGRIAN_FPSCOMPONENT_H

#include "Component.h" // Component

namespace Integrian
{
	class GameObject;
	class TextComponent;
	class FPSComponent final : public Component
	{
	public:
		explicit FPSComponent(GameObject* pParent, TextComponent* pTextComponent);
		virtual ~FPSComponent() = default;

		virtual void Update(const float) override;

		void SetFPS(const int value);

	private:
		TextComponent* m_pTextComponent;
	};
}

#endif // INTEGRIAN_FPSCOMPONENT_H