#pragma once
#include <Component.h>
#include <Libraries/JSON/json.hpp>

namespace Integrian
{
	class GameObject;
	class Texture;
}

class TileFactoryComponent final : public Integrian::Component
{
public:
	TileFactoryComponent(Integrian::GameObject* pParent);

	void CreateTiles(const int level);

	const unsigned int GetSize() const noexcept;
	const int GetLevel() const noexcept;

private:
	Integrian::GameObject* CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture, const unsigned int index);
	void FillConnections(nlohmann::json teleporterLocations) const;
	void CreateTeleportationPads(const int level, nlohmann::json teleporterLocations) const;
	void CreateRedBallSpawner(const unsigned int amountOfRedBalls) const;
	void CreateTileFSM(nlohmann::json tileFSM) const;
	void CreateEnemies(nlohmann::json enemies) const;
	void CreateGraph() const;
	nlohmann::json ReadFile(const int level); // I can't return by reference because it crashes for reasons

	unsigned int m_Size;
	int m_Level;
};