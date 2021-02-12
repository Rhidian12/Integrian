#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: February 2021
// ====================================
#ifndef APP_GRAPPLE_HOOK_H
#define APP_GRAPPLE_HOOK_H

#include "App.h"
// TEXTUREMANAGER is defined in App.h and can be used here
// Texture.h and pch.h were included in App.h and can be used here
class Level;
class Player;
class Grapple_Hook_App final : public Engine::App
{
public:
	Grapple_Hook_App();
	virtual ~Grapple_Hook_App() = default;

	virtual void Start() override;

	virtual void Render() const override;
	virtual void Update(const float elapsedSeconds) override;

	virtual const Engine::Rectf GetLevelBoundaries() const;
	virtual const Engine::Rectf GetTarget() const;

private:
	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<Level> m_pLevel;
};

#endif // !APP_GRAPPLE_HOOK_H