#pragma once
#include <Component.h>
#include <array>

namespace Integrian
{
	class GameObject;
}

enum class Direction : int8_t
{
	LeftBottom = 0,
	LeftTop = 1,
	RightBottom = 2,
	RightTop = 3
};

class TileComponent final : public Integrian::Component
{
public:
	TileComponent(Integrian::GameObject* pParent);

	Integrian::Point2f GetCenter() const noexcept;
	void AddConnection(TileComponent* pTile, const Direction direction);

private:
	Integrian::Point2f m_Center;
	std::array<TileComponent*, 4> m_pConnections; // there are only ever 4 possible connections
	uint8_t m_ActiveConnections;
};