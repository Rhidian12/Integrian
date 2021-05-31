#include "IntegrianPCH.h"
#include "FiniteStateMachine.h"

Integrian::FSMState::FSMState(FSMStateChangeCallback fsmStateChangeCallback, FSMStateUpdateCallback fsmStateFixedUpdateCallback, FSMStateUpdateCallback fsmStateUpdateCallback, FSMStateUpdateCallback fsmStateLateUpdateCallback)
	: m_FSMStateChangeCallback{ fsmStateChangeCallback }
	, m_FSMStateFixedUpdateCallback{ fsmStateFixedUpdateCallback }
	, m_FSMStateUpdateCallback{ fsmStateUpdateCallback }
	, m_FSMStateLateUpdateCallback{ fsmStateLateUpdateCallback }
{
}

void Integrian::FSMState::OnStateChange(Blackboard* pBlackboard, const FSMStateTransition fsmStateTransition)
{
	m_FSMStateChangeCallback(pBlackboard, fsmStateTransition);
}

void Integrian::FSMState::FixedUpdate(Blackboard* pBlackboard, const float elapsedSeconds)
{
	m_FSMStateFixedUpdateCallback(pBlackboard, elapsedSeconds);
}

void Integrian::FSMState::Update(Blackboard* pBlackboard, const float elapsedSeconds)
{
	m_FSMStateUpdateCallback(pBlackboard, elapsedSeconds);
}

void Integrian::FSMState::LateUpdate(Blackboard* pBlackboard, const float elapsedSeconds)
{
	m_FSMStateLateUpdateCallback(pBlackboard, elapsedSeconds);
}

Integrian::FSMTransition::FSMTransition(FSMTransitionCallback callback)
	: m_Callback{ callback }
{
}

bool Integrian::FSMTransition::ToTransition(Blackboard* pBlackboard)
{
	return m_Callback(pBlackboard);
}

Integrian::FiniteStateMachineComponent::FiniteStateMachineComponent(GameObject* pParent, std::shared_ptr<FSMState> pStartState, Blackboard* pBlackboard)
	: Component{ pParent }
	, m_pBlackboard{ pBlackboard }
	, m_pCurrentState{ pStartState }
	, m_pStates{}
{
}

Integrian::FiniteStateMachineComponent::~FiniteStateMachineComponent()
{
	SafeDelete(m_pBlackboard);

	//for (StatePair pair : m_pStates)
	//{
	//	for (StateTransitionPair transitionPair : pair.second)
	//	{
	//		SafeDelete(transitionPair.first);
	//		SafeDelete(transitionPair.second);
	//	}

	//	pair.second.clear();
	//}

	//for (StatePair pair : m_pStates)
	//	SafeDelete(pair.first);
}

void Integrian::FiniteStateMachineComponent::AddTransition(std::shared_ptr<FSMState> pFromState, std::shared_ptr<FSMState> pToState, std::shared_ptr<FSMTransition> pTransition)
{
	m_pStates[pFromState].push_back(std::make_pair(pTransition, pToState));
}

void Integrian::FiniteStateMachineComponent::Update(const float elapsedSeconds)
{
	if (m_pCurrentState)
	{
		for (const StateTransitionPair& pair : m_pStates[m_pCurrentState])
		{
			if (pair.first->ToTransition(m_pBlackboard))
			{
				ChangeState(pair.second);
				break;
			}
		}
	}

	m_pCurrentState->FixedUpdate(m_pBlackboard, elapsedSeconds);
	m_pCurrentState->Update(m_pBlackboard, elapsedSeconds);
	m_pCurrentState->LateUpdate(m_pBlackboard, elapsedSeconds);
}

Integrian::Blackboard* Integrian::FiniteStateMachineComponent::GetBlackboard() const noexcept
{
	return m_pBlackboard;
}

Integrian::FSMState* Integrian::FiniteStateMachineComponent::GetCurrentState() const noexcept
{
	return m_pCurrentState.get();
}

void Integrian::FiniteStateMachineComponent::ChangeState(const std::shared_ptr<FSMState>& pFSMState)
{
	m_pCurrentState->OnStateChange(m_pBlackboard, FSMStateTransition::OnExit);

	m_pCurrentState = pFSMState;

	m_pCurrentState->OnStateChange(m_pBlackboard, FSMStateTransition::OnEnter);
}
