#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
}

class TeleportationPadComponent final : public Integrian::Component
{
public:
	TeleportationPadComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float elapsedSeconds) override;

private:
	Integrian::GameObject* m_pQbert;
	Integrian::Point2f m_EndPosition;
};