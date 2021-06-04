#pragma once
#include <unordered_map>
#include <Component.h>
#include <string>

namespace Integrian
{
	class GameObject; 
	class FiniteStateMachineComponent;
	class Blackboard;
}

class KeyboardExplanationFSM final : public Integrian::Component
{
public:
	KeyboardExplanationFSM(Integrian::GameObject* pParent);

	virtual void PostInitialize() override;

	virtual void Update(const float) override;

	Integrian::FiniteStateMachineComponent* CreateKeyboardFSM() noexcept;

private:
	std::unordered_map<std::string, Integrian::GameObject*> m_pTextComponents;
	Integrian::Blackboard* m_pBlackboard;
};

