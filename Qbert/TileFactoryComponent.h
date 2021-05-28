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

private:
	Integrian::GameObject* CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture);
	void FillConnections();
	nlohmann::json ReadFile(const int level);

	unsigned int m_Size;
};