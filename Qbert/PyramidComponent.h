#pragma once
#include <Component.h>
#include <vector>
#include <ListenerInterface.h>

namespace Integrian
{
	class Texture;
	class GameObject;
}

class TileComponent;
class PyramidComponent final : public Integrian::Component, public Integrian::IListener
{
public:
	PyramidComponent(Integrian::GameObject* pParent);
	virtual ~PyramidComponent() = default;

	virtual void Render() const override;

	virtual void Update(const float elapsedSeconds) override;

	void AddTile(Integrian::GameObject* pTile);
	Integrian::Point2f GetTopTileCenter() const noexcept;

	TileComponent* GetTile(const Integrian::Point2f& location) const;

	const std::vector<Integrian::GameObject*>& GetTiles() const noexcept;

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	std::vector<Integrian::GameObject*> m_pTiles;
};