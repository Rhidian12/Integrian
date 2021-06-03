#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
}

class QbertFSM final : public Integrian::Component
{
public:
	QbertFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

private:
	Integrian::FiniteStateMachineComponent* m_pFSM;
};

