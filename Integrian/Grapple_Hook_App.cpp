#include "Grapple_Hook_App.h"
#include "pch.h"
#include "Texture.h"
#include "Level.h"
#include "Player.h"
#include "OrthographicCamera.h" 
#include "InputManager.h"
Grapple_Hook_App::Grapple_Hook_App()
	// == Make Sure The Player Is Initialized Before The Level ==
	: m_pPlayer{ std::make_unique<Player>(Player{Integrian::Point2f{320.f,50.f} }) }
	, m_pLevel{}
{
}

void Grapple_Hook_App::Start()
{
	m_pLevel = std::make_unique<Level>(Level{ m_WindowWidth,m_WindowHeight, m_pPlayer });
	m_Target = m_pPlayer->GetPlayerAvatar();

	InputManager::GetInstance()->AddMemberFunctionWrapper(SDL_SCANCODE_D, m_pPlayer.get(), &Player::MoveRight, true);
	InputManager::GetInstance()->AddMemberFunctionWrapper(SDL_SCANCODE_A, m_pPlayer.get(), &Player::MoveLeft, true);
	InputManager::GetInstance()->AddMemberFunctionWrapper(SDL_SCANCODE_SPACE, m_pPlayer.get(), &Player::Jump, true);
	InputManager::GetInstance()->AddMemberFunctionWrapper(MouseButton::LMB, m_pPlayer.get(), &Player::HandleGrappleHookShot, true);
	InputManager::GetInstance()->AddMemberFunctionWrapper(MouseButton::LMB, m_pPlayer.get(), &Player::HandleGrappleHookShotReleased, false);
}

void Grapple_Hook_App::Render() const
{
	m_pLevel->Render();
	m_pPlayer->Render();
}

void Grapple_Hook_App::Update(const float elapsedSeconds)
{
	m_pPlayer->Update(elapsedSeconds, m_pLevel);
}

const Integrian::Rectf Grapple_Hook_App::GetLevelBoundaries() const
{
	return m_pLevel->GetLevelBoundaries();
}

const Integrian::Rectf Grapple_Hook_App::GetTarget() const
{
	return m_pPlayer->GetPlayerAvatar();
}
