#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
	class Texture;
}

class TileFactoryComponent final : public Integrian::Component
{
public:
	TileFactoryComponent(Integrian::GameObject* pParent);

	void CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture);

private:
	Integrian::GameObject* CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture);
};