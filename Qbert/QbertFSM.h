#pragma once
#include <Component.h>
#include <PossibleInputs.h>
#include <ListenerInterface.h>
#include <array>
#include <GameInput.h>

namespace Integrian
{
	class GameObject;
	class FiniteStateMachineComponent;
}

enum KeybindMovementDirection
{
	RightTop = 0,
	RightBottom = 1,
	LeftBottom = 2,
	LeftTop = 3
};

class QbertFSM final : public Integrian::Component, public Integrian::IListener
{
public:
	QbertFSM(Integrian::GameObject* pParent, std::array<Integrian::GameInput, 4>&& keybinds);

	virtual void PostInitialize() override;

	void Reset();

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	Integrian::FiniteStateMachineComponent* m_pFSM;
	std::array<Integrian::GameInput, 4> m_Keybinds;
};

