#include "IntegrianPCH.h"
#include "FiniteStateMachine.h"

Integrian::FSMState::FSMState(FSMStateChangeCallback fsmCallback, FSMStateUpdateCallback fsmUpdateCallback)
	: m_FSMStateChangeCallback{ fsmCallback }
	, m_FSMStateUpdateCallback{ fsmUpdateCallback }
{
}

void Integrian::FSMState::OnStateChange(Blackboard* pBlackboard)
{
}

void Integrian::FSMState::Update(Blackboard* pBlackboard, const float elapsedSeconds)
{
}

Integrian::FSMTransition::FSMTransition(FSMTransitionCallback callback)
	: m_Callback{ callback }
{
}

bool Integrian::FSMTransition::ToTransition(Blackboard* pBlackboard)
{
	return m_Callback(pBlackboard);
}