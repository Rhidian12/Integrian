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

	virtual void Render(const Integrian::Point2f&) const override;

	virtual void Update(const float elapsedSeconds) override;

	void AddTile(Integrian::GameObject* pTile);
	Integrian::Point2f GetTopTileCenter() const noexcept;

	const std::vector<Integrian::GameObject*>& GetTiles() const noexcept;

private:
	std::vector<Integrian::GameObject*> m_pTiles;
};