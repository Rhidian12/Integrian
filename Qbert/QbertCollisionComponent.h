#pragma once
#include <Component.h>
#include <vector>

namespace Integrian
{
	class GameObject;
}

class QbertCollisionComponent final : public Integrian::Component
{
public:
	QbertCollisionComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;

private:
	Integrian::GameObject* m_pQbert;

	std::vector<Integrian::GameObject*> m_pEnemies;
};