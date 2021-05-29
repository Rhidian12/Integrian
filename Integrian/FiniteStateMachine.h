#pragma once

#ifndef INTEGRIAN_FINITESTATEMACHINE_H
#define INTEGRIAN_FINITESTATEMACHINE_H

#include "Component.h" // Component
#include "Blackboard.h" // Blackboard
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector

namespace Integrian
{
	class GameObject;

	enum class FSMStateTransition
	{
		OnEnter = 0,
		OnExit = 1
	};

	class FSMState final
	{
	public:
		typedef std::function<void(Blackboard* pBlackboard, const FSMStateTransition transitionState)> FSMStateChangeCallback;
		typedef std::function<void(Blackboard* pBlackboard, const float elapsedSeconds)> FSMStateUpdateCallback;

		FSMState(FSMStateChangeCallback fsmStateChangeCallback, FSMStateUpdateCallback fsmStateUpdateCallback);
		~FSMState() = default;

		void OnStateChange(Blackboard* pBlackboard, const FSMStateTransition fsmStateTransition);
		void Update(Blackboard* pBlackboard, const float elapsedSeconds);

	private:
		FSMStateChangeCallback m_FSMStateChangeCallback;
		FSMStateUpdateCallback m_FSMStateUpdateCallback;
	};

	class FSMTransition final
	{
	public:
		typedef std::function<bool(Blackboard* pBlackboard)> FSMTransitionCallback;
		
		FSMTransition(FSMTransitionCallback callback);
		~FSMTransition() = default;

		bool ToTransition(Blackboard* pBlackboard);

	private:
		FSMTransitionCallback m_Callback;
	};

	class FiniteStateMachineComponent final : public Component
	{
	public:
		FiniteStateMachineComponent(GameObject* pParent, FSMState* pStartState, Blackboard* pBlackboard);
		~FiniteStateMachineComponent();

		void AddTransition(FSMState* pFromState, FSMState* pToState, FSMTransition* pTransition);
		
		virtual void Update(const float elapsedSeconds) override;

		Blackboard* GetBlackboard() const noexcept;
		FSMState* GetCurrentState() const noexcept;

	private:
		void ChangeState(FSMState* pFSMState);

		Blackboard* m_pBlackboard;

		// https://stackoverflow.com/questions/4437862/whats-the-advantage-of-multimap-over-map-of-vectors
		using StateTransitionPair = std::pair<FSMTransition*, FSMState*>;
		using StatePair = std::pair<FSMState*, std::vector<StateTransitionPair>>;

		std::unordered_map<FSMState*, std::vector<StateTransitionPair>> m_pStates;
		FSMState* m_pCurrentState;
	};
}


#endif // !INTEGRIAN_FINITESTATEMACHINE_H