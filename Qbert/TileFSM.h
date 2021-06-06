#pragma once

#include <Component.h>
#include <Blackboard.h>
#include <FiniteStateMachine.h>
#include <ListenerInterface.h>
#include <vector>

namespace Integrian
{
	class GameObject;
	class Texture;
}

enum class TileChange
{
	Permanent = 0,
	Intermediate = 1,
	Revert = 2
};

class TileFSM final : public Integrian::Component, public Integrian::IListener
{
public:
	TileFSM(Integrian::GameObject* pParent);

	Integrian::FiniteStateMachineComponent* CreatePermanentFSM(Integrian::Texture* pInactiveTexture, Integrian::Texture* pActiveTexture);
	Integrian::FiniteStateMachineComponent* CreateIntermediateFSM(Integrian::Texture* pInactiveTexture, Integrian::Texture* pIntermediateTexture, Integrian::Texture* pActiveTexture);
	Integrian::FiniteStateMachineComponent* CreateRevertFSM(Integrian::Texture* pInactiveTexture, Integrian::Texture* pActiveTexture);

	virtual bool OnEvent(const Integrian::Event& event) override;

private:
	Integrian::Blackboard* m_pBlackboard;
};