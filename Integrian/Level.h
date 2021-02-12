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
namespace Integrian
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

	const Integrian::Rectf& GetGround() const;
	const Integrian::Rectf& GetLevelBoundaries() const;
	const std::vector<Integrian::Rectf>& GetBlocks() const;

private:
	Integrian::Texture* m_pBackground;
	uint32_t m_AmountOfVertices;
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;
	float m_MaxDistanceBetweenBlocksToGrappleOn;
	float m_MaxDistancePlayerCanTravel;
	std::vector<Integrian::Rectf> m_BlocksToGrappleOn;
	Integrian::Rectf m_Ground;
	Integrian::Rectf m_LevelBoundaries;
};

#endif // !APP_GRAPPLE_HOOK_LEVEL_H