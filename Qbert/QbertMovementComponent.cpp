#include "QbertMovementComponent.h"
#include <InputManager.h>
#include <GameObject.h>
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"

QbertMovementComponent::QbertMovementComponent(Integrian::GameObject* pParent, const uint8_t index)
	: Component{ pParent }
{
	using namespace Integrian;

	auto movement = [pParent]()
	{
		const Point2f qbertPosition{ pParent->transform.GetPosition() };

		GameObject* pPyramidRoot{ App_Selector::GetInstance().GetActiveApplication()->GetGameObject("PyramidRoot") };

		TileComponent* pQbertTile{ pPyramidRoot->GetComponentByType<PyramidComponent>()->GetTile(qbertPosition) };

		TileComponent* pEndTile{ pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)] };

		if (pEndTile) // is there a connection to the tile
		{

		}
		else // there is no connection == jumping off the map
		{

		}
	};

	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::DPAD_Left }, movement, State::OnPress, index);
}
