#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: January 2021
// ====================================
#ifndef APP_GRAPPLE_HOOK_PLAYER_H
#define APP_GRAPPLE_HOOK_PLAYER_H

#include "pch.h"
#include <memory>
enum class PlayerState
{
	None = 0,
	InTheAir = 1,
	Grappling = 2,
};
class Level;
class Player final
{
public:
	Player(const Engine::Point2f& startPosition);
	~Player() = default;

	void Render() const;

	void Update(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel);

	void MoveRight(const float dt);
	void MoveLeft(const float dt);
	void Jump(const float dt);

	void HandleGrappleHookShot();
	void HandleGrappleHookShotReleased();

	const float GetMaxGrappleRange() const;
	const float GetMaxSpeed() const;
	const Engine::Rectf& GetPlayerAvatar() const;

private:
	void HandleMouseMotion();
	void HandleMovement(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel);
	void CheckLevelBorders(const Engine::Rectf& levelBoundaries, const Engine::Rectf& ground);
	void CheckCollisions(const std::unique_ptr<Level>& pLevel);
	void HandleGrappleHookMovement(const std::unique_ptr<Level>& pLevel, const float elapsedSeconds);
	void HandleGrappleHookMovementOnTheGround();
	void HandleGrappleHookMovementInTheAir(const std::unique_ptr<Level>& pLevel, const float elapsedSeconds);
	bool IsPlayerOnGround(const std::unique_ptr<Level>& pLevel);
	bool IsPlayerOnBlock(const Engine::Point2f& center, const Engine::Point2f& bot, Engine::HitInfo& hitInfo, const Engine::Rectf& block);
	bool IsGrappleHookOnBlock(const Engine::Point2f& startPoint, const Engine::Point2f& endpoint, Engine::HitInfo& hitInfo, const Engine::Rectf& block) const;
	bool IsPlayerInTheAir(const std::unique_ptr<Level>& pLevel);
	void DrawGrappleHook() const;
	void UpdateGrappleHook(const float elapsedSeconds, const std::unique_ptr<Level>& pLevel);

	Engine::Rectf m_PlayerAvatar;
	PlayerState m_PlayerState;
	const float m_Gravity;
	float m_Acceleration;
	float m_MaxSpeed;
	float m_JumpSpeed;
	bool m_HasJumped;
	float m_GrappleRange;
	bool m_IsGrappleAnimationDone;
	bool m_IsGrappleHookTargetSet;
	bool m_IsLMBPressed;
	bool m_IsGrappleHookAttached;
	float m_GrappleHookAnimTime;
	float m_GrappleHookAnimSpeed;
	float m_GrappleHookDistanceSquared;
	Engine::Point2f m_MousePosition;
	Engine::Point2f m_GrappleHookEndPoint;
	Engine::Point2f m_GrappleHookAnimPoint;
	Engine::Vector2f m_TotalDirection;
	Engine::Vector2f m_CurrentDirection;
};

#endif // !APP_GRAPPLE_HOOK_PLAYER_H