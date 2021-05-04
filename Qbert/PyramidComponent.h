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
	virtual ~PyramidComponent();

	virtual void Update(const float elapsedSeconds) override;
	virtual void Render(const Integrian::Point2f& location) const override;

	void CreateTiles(const unsigned int size, Integrian::Texture* pInactiveTileTexture);
	Integrian::GameObject* CreateTile(const Integrian::Point2f& location, Integrian::Texture* pInactiveTileTexture);

private:
	std::vector<Integrian::GameObject*> m_pGameObjects;
};