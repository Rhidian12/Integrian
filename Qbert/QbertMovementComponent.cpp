#include "QbertMovementComponent.h"
#include <InputManager.h>
#include <GameObject.h>
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"
#include <EventQueue.h>
#include <TextureManager.h>
#include "QbertSpriteComponent.h"
#include <Texture.h>
#include "TeleportationPadComponent.h"

QbertMovementComponent::QbertMovementComponent(Integrian::GameObject* pParent, const uint8_t index)
	: Component{ pParent }
	, m_pPyramidComponent{}
	, m_pSpriteComponent{}
	, m_VectorTowardsOtherTile{}
	, m_Velocity{}
	, m_EndPosition{}
	, m_Speed{ 65.f }
	, m_Index{ index }
	, m_CanMoveAgain{ true }
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

	auto movement = [this]()
	{
		if (!m_CanMoveAgain)
			return;

		const Point2f qbertPosition{ m_pParent->transform.GetPosition() };

		TileComponent* pQbertTile{ m_pPyramidComponent->GetTile(qbertPosition) };
		TileComponent* pEndTile{};
		TeleportationPadComponent* pTP{};

		InputManager& inputManager{ InputManager::GetInstance() };

		Vector2f vectorTowardsOtherTile{};

		if (inputManager.IsKeyboardKeyPressed(KeyboardInput::A)) // Left Bottom Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection);

			vectorTowardsOtherTile = Vector2f{ -m_VectorTowardsOtherTile.x, -m_VectorTowardsOtherTile.y };

			Rectf sourceRect{ m_pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += m_pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			m_pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertLeftBottomAnimation"));
			m_pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::D)) // Right Bottom Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection);

			vectorTowardsOtherTile = Vector2f{ m_VectorTowardsOtherTile.x, -m_VectorTowardsOtherTile.y };

			Rectf sourceRect{ m_pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += m_pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			m_pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertRightBottomAnimation"));
			m_pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::Q)) // Left Top Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection);
			else
				pTP = std::get<1>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftTop)].connection);

			vectorTowardsOtherTile = Vector2f{ -m_VectorTowardsOtherTile.x, m_VectorTowardsOtherTile.y };

			Rectf sourceRect{ m_pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += m_pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			m_pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertLeftTopAnimation"));
			m_pSpriteComponent->SetSourceRect(sourceRect);
		}
		else if (inputManager.IsKeyboardKeyPressed(KeyboardInput::E)) // Right Top Movement
		{
			if (std::holds_alternative<TileComponent*>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection))
				pEndTile = std::get<0>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection);
			else
				pTP = std::get<1>(pQbertTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightTop)].connection);

			vectorTowardsOtherTile = m_VectorTowardsOtherTile;

			Rectf sourceRect{ m_pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x += m_pSpriteComponent->GetTexture()->GetWidth() * 0.5f;
			m_pSpriteComponent->SetTexture(TextureManager::GetInstance().GetTexture("QbertRightTopAnimation"));
			m_pSpriteComponent->SetSourceRect(sourceRect);
		}

		if (pEndTile) // is there a connection to the tile
			m_EndPosition = pEndTile->GetCenter();
		else if (pTP) // is there a connection to a teleporter
		{
			m_EndPosition = pTP->GetParent()->transform.GetPosition();
		}
		else // there is no connection == jumping off the map
		{
			m_EndPosition = qbertPosition + vectorTowardsOtherTile;
			EventQueue::GetInstance().QueueEvent(Event{ "QbertMoveOffTheMap" });
		}

		m_CanMoveAgain = false; // make sure we cant move while we're still moving

		m_Velocity = m_EndPosition - qbertPosition;
		Integrian::Normalize(m_Velocity);
	};

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::A }, movement, State::OnPress);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::Q }, movement, State::OnPress);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::E }, movement, State::OnPress);
	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::D }, movement, State::OnPress);
	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::DPAD_Left }, movement, State::OnPress, m_Index);

	m_pSpriteComponent = m_pParent->GetComponentByType<QbertSpriteComponent>();
}

void QbertMovementComponent::Update(const float)
{
	using namespace Integrian;

	if (AreEqual(m_pParent->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, m_EndPosition.y, 1.f))
	{
		if (m_Velocity != Vector2f{})
		{
			Rectf sourceRect{ m_pSpriteComponent->GetSourceRect() };
			sourceRect[VertexLocation::LeftBottom].x = 0.f;
			m_pSpriteComponent->SetSourceRect(sourceRect);
			EventQueue::GetInstance().QueueEvent(Event{ "QbertMovementEnded", m_pPyramidComponent->GetTile(m_EndPosition) });
		}

		m_Velocity = Vector2f{};
		m_pParent->transform.SetPosition(m_EndPosition);

		m_CanMoveAgain = true;
	}
}

void QbertMovementComponent::FixedUpdate(const float elapsedSeconds)
{
	const Integrian::Point2f initialPosition{ m_pParent->transform.GetPosition() };

	const Integrian::Vector2f speed{ m_Velocity * elapsedSeconds * m_Speed };

	m_pParent->transform.SetPosition(initialPosition + speed);
}
