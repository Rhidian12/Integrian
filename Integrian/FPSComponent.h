#pragma once

#ifndef INTEGRIAN_FPSCOMPONENT_H
#define INTEGRIAN_FPSCOMPONENT_H

#include "Component.h"

namespace Integrian
{
	class TextComponent;
	class FPSComponent final : public Component
	{
	public:
		explicit FPSComponent(TextComponent* pTextComponent);
		virtual ~FPSComponent() = default;

		virtual void Update(const float) override;

	private:
		TextComponent* m_pTextComponent;
	};
}

#endif // INTEGRIAN_FPSCOMPONENT_H