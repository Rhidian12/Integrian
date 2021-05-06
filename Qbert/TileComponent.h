#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
}

class TileComponent final : public Integrian::Component
{
public:
	TileComponent(Integrian::GameObject* pParent);

	Integrian::Point2f GetCenter() const noexcept;

private:
	Integrian::Point2f m_Center;
};

struct TileConnection final
{
	std::unique_ptr<TileComponent[]> pConnections = std::make_unique<TileComponent[]>(4);
};
