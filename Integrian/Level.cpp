#include "Level.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Player.h"
#include <algorithm>
Level::Level(const uint32_t windowWidth, const uint32_t windowHeight, const std::unique_ptr<Player>& pPlayer)
	: m_WindowWidth{ windowWidth }
	, m_WindowHeight{ windowHeight }
	, m_AmountOfVertices{ windowWidth / 10 } // we want 10 vertices
	, m_Ground{ 0.f,0.f,float(windowWidth),25.f }
	, m_LevelBoundaries{}
	, m_pBackground{ TextureManager::GetInstance()->GetTextures().find("Background")->second }
	, m_MaxDistanceBetweenBlocksToGrappleOn{ pPlayer->GetMaxGrappleRange() }
	, m_MaxDistancePlayerCanTravel{ pPlayer->GetMaxGrappleRange() + pPlayer->GetMaxSpeed() }
{
	m_LevelBoundaries = Engine::Rectf{ m_Ground.leftBottom.x,m_Ground.leftBottom.y,m_Ground.width,800.f };
	GenerateBlocksToGrappleOn();
}
void Level::Render() const
{
	Engine::DrawFilledRectangle(m_Ground, Engine::RGBColour{ 0.f,0.f,0.f });
	m_pBackground->Draw();

	for (const Engine::Rectf& block : m_BlocksToGrappleOn)
	{
		Engine::DrawFilledRectangle(block, Engine::RGBColour{ 0.f,255.f,0.f });
	}
}
void Level::GenerateBlocksToGrappleOn()
{
	// == This Gives Us How Many Blocks We Need On The Height To Make Sure There Is A Way Up ==
	const int numberOfBlocksToGenerate{ int(m_LevelBoundaries.height / m_MaxDistanceBetweenBlocksToGrappleOn) };
	//const float maxDistanceBetweenBlocks{ m_MaxDistanceBetweenBlocksToGrappleOn };
	const float maxDistanceBetweenBlocks{ m_MaxDistancePlayerCanTravel };
	for (int i{}; i < numberOfBlocksToGenerate; ++i)
	{
		Engine::Rectf block{};
		block.width = 20.f;
		block.height = 10.f;
		bool isRandomPositionValid{};

		do
		{
			const float randomXPos{ Engine::RandomNumber(m_LevelBoundaries.leftBottom.x,m_LevelBoundaries.width) };
			// == Make Sure X Position Is In Bounds ==
			if (randomXPos + block.width >= m_LevelBoundaries.width || randomXPos <= m_LevelBoundaries.leftBottom.x)
				continue;

			float randomYPos{};
			if (m_BlocksToGrappleOn.empty())
			{
				// Y position must be between the current block and the Max Grapple Range
				const float minimumYPos{ (m_BlocksToGrappleOn.size() + 1) * block.height + m_Ground.height };
				randomYPos = Engine::RandomNumber(minimumYPos, minimumYPos + maxDistanceBetweenBlocks);
			}
			else
			{
				const float minimumYPos{ m_BlocksToGrappleOn[uint64_t(i) - 1].leftBottom.y };
				randomYPos = Engine::RandomNumber(minimumYPos + block.height, minimumYPos + block.height + maxDistanceBetweenBlocks);
			}

			const Engine::Point2f randomPosition{ randomXPos,randomYPos };
			// Make Sure That Random Position Is Not Too Far Away From Any Block
			// If There Are No Other Blocks, Make Sure That The Block Is Not Too Far Away From Ground
			// The Block Must Also Go A Bit Up
			if (m_BlocksToGrappleOn.empty())
			{
				// == Check With The Ground ==
				const Engine::Point2f pointOnGround{ randomXPos,m_Ground.height };
				if (Engine::DistanceSquared(randomPosition, pointOnGround) <= Engine::Square(maxDistanceBetweenBlocks))
				{
					block.leftBottom = randomPosition;
					isRandomPositionValid = true;
				}
			}
			else
			{
				// == Check With Other Blocks ==
				if (Engine::DistanceSquared(randomPosition, m_BlocksToGrappleOn[uint64_t(i) - 1].leftBottom) <= Engine::Square(maxDistanceBetweenBlocks))
				{
					block.leftBottom = randomPosition;
					isRandomPositionValid = true;
				}
			}

			// Make Sure That There Is A Way Up
		} while (!isRandomPositionValid);

		m_BlocksToGrappleOn.push_back(block);
	}
}
const Engine::Rectf& Level::GetGround() const
{
	return m_Ground;
}
const Engine::Rectf& Level::GetLevelBoundaries() const
{
	return m_LevelBoundaries;
}

const std::vector<Engine::Rectf>& Level::GetBlocks() const
{
	return m_BlocksToGrappleOn;
}
