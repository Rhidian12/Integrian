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

	virtual void Update(const float elapsedSeconds) override;

	void AddTile(Integrian::GameObject* pTile);

private:
	std::vector<Integrian::GameObject*> m_pTiles;
};