#pragma once
#include <Component.h>
#include <array>
#include <variant>

namespace Integrian
{
	class GameObject;
}

enum class Direction : uint8_t
{
	LeftBottom = 0,
	LeftTop = 1,
	RightBottom = 2,
	RightTop = 3
};

class TeleportationPadComponent;
class TileComponent;

struct Connection final
{
	Connection()
		: connection{}
	{}
	Connection(TileComponent* pTileComponent)
		: connection{pTileComponent}
	{}
	Connection(TeleportationPadComponent* pTeleportationPadComponent)
		: connection{pTeleportationPadComponent}
	{}

	std::variant<TileComponent*, TeleportationPadComponent*> connection;
};

class TileComponent final : public Integrian::Component
{
public:
	TileComponent(Integrian::GameObject* pParent, const unsigned int index);

	Integrian::Point2f GetCenter() const noexcept;
	void AddConnection(TileComponent* pTile, const Direction direction);
	void AddConnection(TeleportationPadComponent* pTile, const Direction direction);

	void SetConnection(const Direction direction, const Connection& connection);
	[[nodiscard]] const std::array<Connection, 4>& GetConnections() const noexcept;

	[[nodiscard]] const unsigned int GetIndex() const noexcept;

private:
	Integrian::Point2f m_Center;
	std::array<Connection, 4> m_pConnections; // there are only ever 4 possible connections
	uint8_t m_ActiveConnections;
	unsigned int m_Index;
};