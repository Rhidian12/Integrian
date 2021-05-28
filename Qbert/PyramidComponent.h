#pragma once
#include <Component.h>
#include <vector>

namespace Integrian
{
	class Texture;
	class GameObject;
}

class TileComponent;
class PyramidComponent final : public Integrian::Component
{
public:
	PyramidComponent(Integrian::GameObject* pParent, const int level);
	virtual ~PyramidComponent() = default;

	virtual void Render(const Integrian::Point2f&) const override;

	virtual void Update(const float elapsedSeconds) override;

	void AddTile(Integrian::GameObject* pTile);
	Integrian::Point2f GetTopTileCenter() const noexcept;

	TileComponent* GetTile(const Integrian::Point2f& location) const;

	const std::vector<Integrian::GameObject*>& GetTiles() const noexcept;

private:
	std::vector<Integrian::GameObject*> m_pTiles;
	int m_Level;
};