#include "Player.h"
#include "Level.h"
#include "Timer.h"
#include "InputManager.h"
#include <iostream>
#include <vector>

Player::Player(const Engine::Point2f& startPosition)
// == These Values Seem To Work Fine ==
	: m_PlayerAvatar{ startPosition,10.f,10.f }
	, m_PlayerState{ PlayerState::None }
	, m_Gravity{ 9.81f }
	, m_Acceleration{ 5.f }
	, m_JumpSpeed{ 9.81f * 40.f }
	, m_TotalDirection{}
	, m_CurrentDirection{}
	, m_MaxSpeed{ 2.25f }
	, m_HasJumped{}
	, m_GrappleRange{ 80.f }
	, m_MousePosition{}
	, m_IsGrappleHookTargetSet{}
	, m_IsLMBPressed{}
	, m_IsGrappleHookAttached{}
	, m_GrappleHookAnimTime{}
	, m_GrappleHookAnimSpeed{ 4.f }
	, m_GrappleHookDistanceSquared{}
	, m_GrappleHookEndPoint{}
	, m_GrappleHookAnimPoint{}
	, m_IsGrappleAnimationDone{}
{
}
void Player::Render() const
{
	DrawGrappleHook();
	Engine::DrawFilledRectangle(m_PlayerAvatar, Engine::RGBColour{ 255.f,0.f,0.f });
}
void Player::Update(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel)
{
	switch (m_PlayerState)
	{
	case PlayerState::None:
		//std::cout << "Player State: " << "None" << std::endl;
		break;
	case PlayerState::InTheAir:
		//std::cout << "Player State: " << "InTheAir" << std::endl;
		break;
	case PlayerState::Grappling:
		//std::cout << "Player State: " << "Grappling" << std::endl;
		break;
	}
	HandleMovement(elapsedSeconds, pLevel);
	HandleMouseMotion();
	UpdateGrappleHook(elapsedSeconds, pLevel);
}
void Player::MoveRight(const float dt)
{
	const Engine::Vector2f previousVector{ m_TotalDirection };
	m_TotalDirection.x = previousVector.x + dt * m_Acceleration; // Vt = DeltaT * a + VorigeSnelheid
}
void Player::MoveLeft(const float dt)
{
	const Engine::Vector2f previousVector{ m_TotalDirection };
	m_TotalDirection.x = previousVector.x - dt * m_Acceleration; // Vt = DeltaT * a + VorigeSnelheid
}
void Player::Jump(const float dt)
{
	const Engine::Vector2f previousVector{ m_TotalDirection };
	if (!m_HasJumped)
	{
		m_TotalDirection.y = previousVector.y + dt * m_JumpSpeed; // Vt = DeltaT * a + VorigeSnelheid
		// == Make Sure We Cannot Infinitely Jump ==
		m_HasJumped = true;
	}
}
void Player::HandleMovement(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel)
{
	// == Speed Check ==
	m_TotalDirection.x = Engine::Clamp(m_TotalDirection.x, -m_MaxSpeed, m_MaxSpeed);
	if (Engine::AreEqual(m_TotalDirection.x, 0.f)) // == Set Speed to 0 if it is basically 0 (Makes Debugging Easier) ==
		m_TotalDirection.x = 0.f;

	m_TotalDirection.y = Engine::Clamp(m_TotalDirection.y, -m_MaxSpeed, m_MaxSpeed);
	if (Engine::AreEqual(m_TotalDirection.y, 0.f)) // == Set Speed to 0 if it is basically 0 (Makes Debugging Easier) ==
		m_TotalDirection.y = 0.f;

	// == Apply Gravity If Player Is In The Air ==
	if (IsPlayerInTheAir(pLevel))
	{
		m_TotalDirection.y -= elapsedSeconds * m_Gravity; // == Doing This Makes Mass 1 kg ==
		m_TotalDirection.y = Engine::Clamp(m_TotalDirection.y, -m_Gravity, m_MaxSpeed);
	}
	else
	{
		const Engine::Point2f rightPlayerCenter{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
		const Engine::Point2f rightPlayerBot{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y };
		const Engine::Point2f leftPlayerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
		const Engine::Point2f leftPlayerBot{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y };
		Engine::HitInfo hitInfo{};
		bool isPlayerOnBlock{};
		for (const Engine::Rectf& block : pLevel->GetBlocks())
		{
			if (IsPlayerOnBlock(rightPlayerCenter, rightPlayerBot, hitInfo, block) || IsPlayerOnBlock(leftPlayerCenter, leftPlayerBot, hitInfo, block))
			{
				isPlayerOnBlock = true;
				break;
			}
		}

		// == Apply Friction ==
		float friction{}; // Value in range [0.f, 1.f] where 1.f is no friction
		if (isPlayerOnBlock)
			friction = 0.5f;
		else
			friction = 0.9f;

		m_TotalDirection.x *= friction;
	}

	// == If Player Is Falling AND Is On The Ground, He Can Jump ==
	if (m_HasJumped)
		if (m_TotalDirection.y <= 0.f && !IsPlayerInTheAir(pLevel)) // == Player HAS To Fall, Since The Rectangle Check Is Too Accurate Or Not Accurate ==
			m_HasJumped = false;

	CheckCollisions(pLevel);
	HandleGrappleHookMovement(pLevel, elapsedSeconds);
	CheckLevelBorders(pLevel->GetLevelBoundaries(), pLevel->GetGround());

	//std::cout << m_TotalDirection;
	// == Apply Force To Player ==
	m_PlayerAvatar.leftBottom += m_TotalDirection;
}
bool Player::IsPlayerOnGround(const std::unique_ptr<Level>& pLevel)
{
	// == Check If We're On The Ground ==
	const Engine::Rectf groundHitBox{ pLevel->GetGround().leftBottom, pLevel->GetGround().width, pLevel->GetGround().height };

	if (Engine::IsOverlapping(m_PlayerAvatar, groundHitBox))
	{
		return true;
	}
	else
	{
		m_PlayerState = PlayerState::InTheAir;
		return false;
	}
}
bool Player::IsPlayerOnBlock(const Engine::Point2f& center, const Engine::Point2f& bot, Engine::HitInfo& hitInfo, const Engine::Rectf& block)
{
	std::vector<Engine::Point2f> blockPoints
	{
		Engine::Point2f{block.leftBottom.x + block.width, block.leftBottom.y + block.height},
		Engine::Point2f{block.leftBottom.x, block.leftBottom.y + block.height},
	};
	return (Engine::Raycast(blockPoints, center, bot, hitInfo) && m_TotalDirection.y <= 0.f);
}
bool Player::IsGrappleHookOnBlock(const Engine::Point2f& startPoint, const Engine::Point2f& endpoint, Engine::HitInfo& hitInfo, const Engine::Rectf& block) const
{
	std::vector<Engine::Point2f> blockPoints
	{
		block.leftBottom,
		Engine::Point2f{block.leftBottom.x + block.width, block.leftBottom.y},
		Engine::Point2f{block.leftBottom.x + block.width, block.leftBottom.y + block.height},
		Engine::Point2f{block.leftBottom.x, block.leftBottom.y + block.height},
	};
	return Engine::Raycast(blockPoints, startPoint, endpoint, hitInfo);
}
bool Player::IsPlayerInTheAir(const std::unique_ptr<Level>& pLevel)
{
	const Engine::Rectf groundHitBox{ pLevel->GetGround().leftBottom, pLevel->GetGround().width, pLevel->GetGround().height };
	if (Engine::IsOverlapping(m_PlayerAvatar, groundHitBox))
		return false;

	const Engine::Point2f rightPlayerCenter{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y };
	const Engine::Point2f rightPlayerBot{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y };
	const Engine::Point2f leftPlayerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	const Engine::Point2f leftPlayerBot{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y };
	Engine::HitInfo hitInfo{};
	for (const Engine::Rectf& block : pLevel->GetBlocks())
		if (IsPlayerOnBlock(rightPlayerCenter, rightPlayerBot, hitInfo, block) || IsPlayerOnBlock(leftPlayerCenter, leftPlayerBot, hitInfo, block))
			return false;

	return true;
}
void Player::CheckLevelBorders(const Engine::Rectf& levelBoundaries, const Engine::Rectf& ground)
{
	// == Boundary Checks ==
	if (m_PlayerAvatar.leftBottom.x < levelBoundaries.leftBottom.x)
		m_PlayerAvatar.leftBottom.x = levelBoundaries.leftBottom.x;
	if (m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width > levelBoundaries.leftBottom.x + levelBoundaries.width)
		m_PlayerAvatar.leftBottom.x = levelBoundaries.leftBottom.x + levelBoundaries.width - m_PlayerAvatar.width;
	if (m_PlayerAvatar.leftBottom.y > levelBoundaries.leftBottom.y + levelBoundaries.height)
		m_PlayerAvatar.leftBottom.y = levelBoundaries.leftBottom.y + levelBoundaries.height;

	// == Seperate Safety/Collision Checks With The Ground ==
	if (m_PlayerAvatar.leftBottom.y < (ground.leftBottom.y + ground.height))
	{
		m_PlayerAvatar.leftBottom.y = (ground.leftBottom.y + ground.height);
		m_TotalDirection.y = 0.f;
	}
}
void Player::CheckCollisions(const std::unique_ptr<Level>& pLevel)
{
	const Engine::Point2f rightPlayerCenter{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	const Engine::Point2f rightPlayerBot{ m_PlayerAvatar.leftBottom.x, m_PlayerAvatar.leftBottom.y };
	const Engine::Point2f leftPlayerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	const Engine::Point2f leftPlayerBot{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width, m_PlayerAvatar.leftBottom.y };
	for (const Engine::Rectf& block : pLevel->GetBlocks())
	{
		Engine::HitInfo hitInfo{};
		if (IsPlayerOnBlock(rightPlayerCenter, rightPlayerBot, hitInfo, block) || IsPlayerOnBlock(leftPlayerCenter, leftPlayerBot, hitInfo, block))
		{
			//m_PlayerAvatar.leftBottom.y = block.leftBottom.y + block.height + 0.5f;
			m_PlayerAvatar.leftBottom.y = hitInfo.intersectPoint.y;
			m_TotalDirection.y = 0.f;
			m_HasJumped = false;
			break; // == We Can Only Be On One Platform, No Need To Check Any Further ==
		}
	}
}
void Player::HandleGrappleHookMovement(const std::unique_ptr<Level>& pLevel, const float elapsedSeconds)
{
	if (m_IsGrappleHookAttached)
	{
		if (IsPlayerInTheAir(pLevel))
			HandleGrappleHookMovementInTheAir(pLevel, elapsedSeconds);
		else
			HandleGrappleHookMovementOnTheGround();
	}
}
void Player::HandleGrappleHookMovementOnTheGround()
{
	const Engine::Point2f playerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width / 2.f, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	if (Engine::DistanceSquared(playerCenter, m_GrappleHookAnimPoint) >= m_GrappleHookDistanceSquared)
	{
		if (!Engine::AreEqual(m_TotalDirection.x, 0.f))
		{
			if (m_TotalDirection.x > 0.f)
				m_PlayerAvatar.leftBottom.x -= 1.f;
			if (m_TotalDirection.x < 0.f)
				m_PlayerAvatar.leftBottom.x += 1.f;

			m_TotalDirection.x = 0.f;
		}
	}
}
void Player::HandleGrappleHookMovementInTheAir(const std::unique_ptr<Level>& pLevel, const float elapsedSeconds)
{
	const Engine::Point2f playerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width / 2.f, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	if (Engine::DistanceSquared(playerCenter, m_GrappleHookAnimPoint) >= m_GrappleHookDistanceSquared)
	{
		if (!Engine::AreEqual(m_TotalDirection.x, 0.f))
		{
			if (m_TotalDirection.x > 0.f)
				m_TotalDirection.x = m_TotalDirection.x - elapsedSeconds * m_Acceleration;
			if (m_TotalDirection.x < 0.f)
				m_TotalDirection.x = m_TotalDirection.x + elapsedSeconds * m_Acceleration;
		}

		if (!Engine::AreEqual(m_TotalDirection.y, 0.f))
		{
			if (m_TotalDirection.y < 0.f) // == The Only Force That Can Work Downward Is Gravity ==
				m_TotalDirection.y = 0.f;
			//m_TotalDirection.y += elapsedSeconds * m_Gravity;
		}
	}
}
void Player::HandleMouseMotion()
{
	m_MousePosition = InputManager::GetInstance()->GetMousePosition();
}

void Player::HandleGrappleHookShot()
{
	if (!m_IsGrappleHookTargetSet)
	{
		// == Left Mouse Button Is Pressed ==

		// == Make Sure The End Point Of The Grapple Hook Is Within Range ==
		const Engine::Point2f playerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width / 2.f, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
		if (Engine::DistanceSquared(playerCenter, m_MousePosition) >= m_GrappleRange * m_GrappleRange)
		{
			const Engine::Vector2f direction{ Engine::GetNormalized(Engine::Vector2f{playerCenter,m_MousePosition}) };
			m_GrappleHookEndPoint = playerCenter + direction * m_GrappleRange;
		}
		else
			m_GrappleHookEndPoint = m_MousePosition;

		m_PlayerState = PlayerState::Grappling;
		m_IsGrappleAnimationDone = false;
		m_IsLMBPressed = true;
		m_IsGrappleHookTargetSet = true;
		m_GrappleHookAnimTime = 0.f;
		m_GrappleHookDistanceSquared = Engine::DistanceSquared(playerCenter, m_GrappleHookEndPoint);
	}
}

void Player::HandleGrappleHookShotReleased()
{
	if (m_IsLMBPressed)
	{
		m_IsLMBPressed = false;
		m_IsGrappleHookTargetSet = false;
		m_IsGrappleHookAttached = false;

		// == Reset Animation ==
		m_GrappleHookAnimTime = 0.f;
		m_IsGrappleAnimationDone = true;
		m_IsGrappleHookTargetSet = false;

		m_GrappleHookAnimPoint = {};
	}
}

void Player::DrawGrappleHook() const
{
	if (m_IsLMBPressed && (!m_IsGrappleAnimationDone || m_IsGrappleHookAttached))
	{
		const Engine::Point2f playerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width / 2.f, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
		Engine::DrawLine(playerCenter, m_GrappleHookAnimPoint, Engine::RGBColour{ 255.f,0.f,255.f }, 3.f);
	}
}

void Player::UpdateGrappleHook(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel)
{
	const Engine::Point2f playerCenter{ m_PlayerAvatar.leftBottom.x + m_PlayerAvatar.width / 2.f, m_PlayerAvatar.leftBottom.y + m_PlayerAvatar.height / 2.f };
	if (m_IsLMBPressed)
	{
		if (!m_IsGrappleHookAttached)
		{
			for (const Engine::Rectf& block : pLevel->GetBlocks())
			{
				Engine::HitInfo hitInfo{};
				if (IsGrappleHookOnBlock(playerCenter, m_GrappleHookAnimPoint, hitInfo, block))
				{
					m_IsGrappleAnimationDone = true;
					m_GrappleHookAnimPoint = hitInfo.intersectPoint;
					m_IsGrappleHookAttached = true;
					break; // == The Grapple Hook Can Only Be Attached To One Block ==
				}
				else
					m_IsGrappleHookAttached = false;
			}
		}
		if (!m_IsGrappleAnimationDone)
		{
			m_GrappleHookAnimTime += m_GrappleHookAnimSpeed * elapsedSeconds;
			const Engine::Vector2f direction{ Engine::GetNormalized(Engine::Vector2f{playerCenter,m_GrappleHookEndPoint}) };
			m_GrappleHookAnimPoint = playerCenter + direction * (m_GrappleRange * m_GrappleHookAnimTime);

			if (Engine::AreEqual(Engine::DistanceSquared(playerCenter, m_GrappleHookAnimPoint), m_GrappleHookDistanceSquared, 10.f * 10.f))
			{
				// == Reset Animation ==
				m_GrappleHookAnimTime = 0.f;
				m_IsGrappleAnimationDone = true;
				m_IsGrappleHookTargetSet = false;
			}
		}
	}
}

const Engine::Rectf& Player::GetPlayerAvatar() const
{
	return m_PlayerAvatar;
}

const float Player::GetMaxGrappleRange() const
{
	return m_GrappleRange;
}

const float Player::GetMaxSpeed() const
{
	return m_MaxSpeed;
}
