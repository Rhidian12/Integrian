#pragma once
// ====================================
// Author: Rhidian De Wit
// December 2020 ---- Last Edited: January 2021
// ====================================
#ifndef APP_GRAPPLE_HOOK_LEVEL_H
#define APP_GRAPPLE_HOOK_LEVEL_H

#include "pch.h"
#include <vector>
#include <memory>
namespace Engine
{
	class Texture;
}
class Player;

class Level final
{
public:
	Level(const uint32_t windowWidth, const uint32_t windowHeight, const std::unique_ptr<Player>& pPlayer);
	~Level() = default;

	void Render() const;

	void GenerateBlocksToGrappleOn();

	const Engine::Rectf& GetGround() const;
	const Engine::Rectf& GetLevelBoundaries() const;
	const std::vector<Engine::Rectf>& GetBlocks() const;

private:
	Engine::Texture* m_pBackground;
	uint32_t m_AmountOfVertices;
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;
	float m_MaxDistanceBetweenBlocksToGrappleOn;
	float m_MaxDistancePlayerCanTravel;
	std::vector<Engine::Rectf> m_BlocksToGrappleOn;
	Engine::Rectf m_Ground;
	Engine::Rectf m_LevelBoundaries;
};

#endif // !APP_GRAPPLE_HOOK_LEVEL_H