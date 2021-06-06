#pragma once
#include <Component.h>
#include <vector>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
}

class SlickSpawnerComponent final : public Integrian::Component
{
public:
	SlickSpawnerComponent(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float dt) override;

private:
	Integrian::FiniteStateMachineComponent* CreateSlickFiniteStateMachine(Integrian::GameObject* pParent) const;
	Integrian::FiniteStateMachineComponent* CreateSamFiniteStateMachine(Integrian::GameObject* pParent) const;

	std::vector<Integrian::GameObject*> m_pSlickAndSam;

	float m_CurrentTime;
	float m_WaitTimer;
};

