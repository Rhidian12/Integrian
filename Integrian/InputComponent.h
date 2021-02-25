#pragma once
#ifndef INTEGRIAN_INPUTCOMPONENT_H
#define INTEGRIAN_INPUTCOMPONENT_H

#include "Component.h"
#include "GameInput.h"

namespace Integrian
{
	class Command;
	class InputComponent : public Component
	{
	public:
		InputComponent() = default;
		virtual ~InputComponent() = default;

		void AddInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex = 0);
		[[nodiscard]] bool IsPressed(const GameInput& gameInput, const uint8_t playerIndex = 0) const;
		[[nodiscard]] const Point2f GetMousePosition() const;

	private:
		
	};
}

#endif // !INTEGRIAN_INPUTCOMPONENT_H