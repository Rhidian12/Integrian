#include "QbertMovementComponent.h"
#include <InputManager.h>

QbertMovementComponent::QbertMovementComponent(Integrian::GameObject* pParent, const uint8_t index)
	: Component{ pParent }
{
	using namespace Integrian;

	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::DPAD_Left }, [pParent]()
		{

		},
		State::OnPress, index);
}
