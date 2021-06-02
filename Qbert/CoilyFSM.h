#pragma once
#include <Component.h>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
}

class CoilyFSM final : public Integrian::Component
{
public:
	CoilyFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

private:
	
};