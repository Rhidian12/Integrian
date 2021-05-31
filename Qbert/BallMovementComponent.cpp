#include "BallMovementComponent.h"
#include "GameObject.h"
#include <App_Selector.h>
#include <App.h>
#include "PyramidComponent.h"
#include "TileComponent.h"
#include <TextureComponent.h>

BallMovementComponent::BallMovementComponent(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_Speed{ 50.f }
	, m_Velocity{}
	, m_pPyramid{}
	, m_pSprite{}
	, m_VectorTowardsOtherTile{}
	, m_EndPosition{}
	, m_BallWaitTimer{ 0.5f }
	, m_CurrentWaitTimer{}
{
}

void BallMovementComponent::PostInitialize()
{
	using namespace Integrian;

	App* const pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };
	m_pPyramid = pActiveApp->GetGameObject("PyramidRoot")->GetComponentByType<PyramidComponent>();

	m_pSprite = m_pParent->GetComponentByType<TextureComponent>();

	m_VectorTowardsOtherTile = { // vector towards right bottom
	m_pPyramid->GetTiles()[0]->GetComponentByType<TileComponent>()->GetCenter(),
	m_pPyramid->GetTiles()[1]->GetComponentByType<TileComponent>()->GetCenter() };
}

void BallMovementComponent::Update(const float dt)
{
	using namespace Integrian;

	if (HasBallReachedEndpoint())
	{
		m_pParent->transform.SetPosition(m_EndPosition);
		m_Velocity = Vector2f{};

		// Change sprite
		Rectf sourceRect{ m_pSprite->GetSourceRect() };
		sourceRect[VertexLocation::LeftBottom].x = 0.f;
		m_pSprite->SetSourceRect(sourceRect);

		m_CurrentWaitTimer += dt;
		if (m_CurrentWaitTimer >= m_BallWaitTimer)
		{
			m_CurrentWaitTimer = 0.f;
		}
		else
			return;
	}
	else
		return;

	const Point2f ballPosition{ m_pParent->transform.GetPosition() };
	TileComponent* const pBallTile{ m_pPyramid->GetTile(ballPosition) };

	if (!pBallTile) // if we're not on a tile, it means we're from the pyramid and should be deleted
	{
		m_pParent->MarkForDeletion();
		m_pParent->SetIsActive(false);
	}

	const std::variant leftBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::LeftBottom)].connection };
	TileComponent* const pLeftTile{ std::holds_alternative<TileComponent*>(leftBottomDirection) ? std::get<0>(leftBottomDirection) : nullptr };

	const std::variant rightBottomDirection{ pBallTile->GetConnections()[static_cast<std::underlying_type_t<Direction>>(Direction::RightBottom)].connection };
	TileComponent* const pRightTile{ std::holds_alternative<TileComponent*>(rightBottomDirection) ? std::get<0>(rightBottomDirection) : nullptr };

	if (pLeftTile && pRightTile)
	{
		// can move both left bottom and right bottom so take a random direction
		const int randomDirection{ rand() % 2 }; // 0 == left, 1 == right

		if (randomDirection == 0) // go left
		{
			m_Velocity = GetNormalized(Vector2f{ -m_VectorTowardsOtherTile.x, m_VectorTowardsOtherTile.y });
			m_EndPosition = pLeftTile->GetCenter();
		}

		else // go right
		{
			m_Velocity = GetNormalized(m_VectorTowardsOtherTile);
			m_EndPosition = pRightTile->GetCenter();
		}
	}
	else if (pLeftTile && !pRightTile)
	{
		// can only move left, so move left
		m_Velocity = GetNormalized(Vector2f{ -m_VectorTowardsOtherTile.x, m_VectorTowardsOtherTile.y });
		m_EndPosition = pLeftTile->GetCenter();
	}
	else if (!pLeftTile && pRightTile)
	{
		// can only move right, so move right
		m_Velocity = GetNormalized(m_VectorTowardsOtherTile);
		m_EndPosition = pRightTile->GetCenter();
	}
	else
	{
		// cannot move in general, so we're at the bottom of the pyramid and are going to die
		// do jump off the pyramid, we'll jump left cus I hate right
		m_Velocity = GetNormalized(m_VectorTowardsOtherTile);
	}

	// Change sprite
	Rectf sourceRect{ m_pSprite->GetSourceRect() };
	sourceRect[VertexLocation::LeftBottom].x = sourceRect.GetWidth() * 0.5f;
	m_pSprite->SetSourceRect(sourceRect);
}

void BallMovementComponent::FixedUpdate(const float dt)
{
	using namespace Integrian;

	const Integrian::Point2f initialPosition{ m_pParent->transform.GetPosition() };

	const Integrian::Vector2f speed{ m_Velocity * dt * m_Speed };

	m_pParent->transform.SetPosition(initialPosition + speed);
}

bool BallMovementComponent::HasBallReachedEndpoint() const noexcept
{
	using namespace Integrian;

	return (AreEqual(m_pParent->transform.GetPosition().x, m_EndPosition.x, 1.f) && AreEqual(m_pParent->transform.GetPosition().y, m_EndPosition.y, 1.f));
}
