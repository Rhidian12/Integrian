#include "QbertMovementComponent.h"
#include <InputManager.h>
#include <GameObject.h>
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"

QbertMovementComponent::QbertMovementComponent(Integrian::GameObject* pParent, const uint8_t index)
	: Component{ pParent }
	, m_pPyramidComponent{}
	, m_VectorTowardsOtherTile{}
	, m_Velocity{}
	, m_EndPosition{}
	, m_Speed{ 100.f }
	, m_Index{ index }
{
}

void QbertMovementComponent::PostInitialize()
{
	using namespace Integrian;

	GameObject* pPyramidRoot{ App_Selector::GetInstance().GetActiveApplication()->GetGameObject("PyramidRoot") };
	m_pPyramidComponent = pPyramidRoot->GetComponentByType<PyramidComponent>();

	m_VectorTowardsOtherTile = { // vector towards right top
		m_pPyramidComponent->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter(),
		m_pPyramidComponent->GetTiles()[0]->GetComponentByType<TileComponent>()->GetCenter() };

	auto leftBottomMovement = [this]()
	{
		const Point2f qbertPosition{ m_pParent->transform.GetPosition() };

		TileComponent* pQbertTile{ m_pPyramidComponent->GetTile(qbertPosition) };
		TileComponent* pEndTile{ pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)] };

		if (pEndTile) // is there a connection to the tile
			m_EndPosition = pEndTile->GetCenter();
		else // there is no connection == jumping off the map
			m_EndPosition = qbertPosition + Vector2f{ -m_VectorTowardsOtherTile.x, -m_VectorTowardsOtherTile.y };

		m_Velocity = m_EndPosition - qbertPosition;
		Integrian::Normalize(m_Velocity);
	};

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::A }, leftBottomMovement, State::OnRelease);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::DPAD_Left }, leftBottomMovement, State::OnPress, m_Index);
}

void QbertMovementComponent::Update(const float)
{
	using namespace Integrian;

	if (AreEqual(m_pParent->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, m_EndPosition.y, 1.f))
	{
		m_Velocity = Integrian::Vector2f{};
		m_pParent->transform.SetPosition(m_EndPosition);
	}
}

void QbertMovementComponent::FixedUpdate(const float elapsedSeconds)
{
	const Integrian::Point2f initialPosition{ m_pParent->transform.GetPosition() };

	const Integrian::Vector2f speed{ m_Velocity * elapsedSeconds * m_Speed };

	m_pParent->transform.SetPosition(initialPosition + speed);
}
