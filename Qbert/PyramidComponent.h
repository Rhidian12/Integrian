#pragma once
#include <Component.h>
#include <vector>

namespace Integrian
{
	class Texture;
	class GameObject;
}

class PyramidComponent final : public Integrian::Component
{
public:
	PyramidComponent(Integrian::GameObject* pParent);
	virtual ~PyramidComponent() = default;

	Integrian::GameObject* CreateTile(Integrian::Texture* pInactiveTileTexture, Integrian::Texture* pActiveTileTexture);

private:
	std::vector<Integrian::GameObject*> m_pGameObjects;
};