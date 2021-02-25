#include "pch.h"
#include "InputComponent.h"
#include "InputManager.h"

void Integrian::InputComponent::AddInput(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	InputManager::GetInstance().AddCommand(gameInput, pCommand, keyState, controllerIndex);
}

bool Integrian::InputComponent::IsPressed(const GameInput& gameInput, const uint8_t playerIndex) const
{
	if (gameInput.controllerInput != ControllerInput::INVALID)
		return InputManager::GetInstance().IsControllerButtonPressed(gameInput.controllerInput, playerIndex);

	if (gameInput.keyboardInput != KeyboardInput::INVALID)
		return InputManager::GetInstance().IsKeyboardKeyPressed(gameInput.keyboardInput);

	if (gameInput.mouseButton != MouseButton::INVALID)
		return InputManager::GetInstance().IsMouseButtonPressed(gameInput.mouseButton);
}

const Integrian::Point2f Integrian::InputComponent::GetMousePosition() const
{
	return InputManager::GetInstance().GetMousePosition();
}
