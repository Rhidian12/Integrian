#pragma once

#ifndef INTEGRIAN_FINITESTATEMACHINE_H
#define INTEGRIAN_FINITESTATEMACHINE_H

#include "Component.h" // Component
#include "Blackboard.h" // Blackboard
#include <unordered_map> // std::unordered_map
#include <vector> // std::vector
#include <memory> // std::shared_ptr

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

		FSMState(FSMStateChangeCallback fsmStateChangeCallback = [](Blackboard*, const FSMStateTransition) {},
			FSMStateUpdateCallback fsmStateFixedUpdateCallback = [](Blackboard*, const float) {},
			FSMStateUpdateCallback fsmStateUpdateCallback = [](Blackboard*, const float) {},
			FSMStateUpdateCallback fsmStateLateUpdateCallback = [](Blackboard*, const float) {});
		~FSMState() = default;

		void OnStateChange(Blackboard* pBlackboard, const FSMStateTransition fsmStateTransition);
		void FixedUpdate(Blackboard* pBlackboard, const float elapsedSeconds);
		void Update(Blackboard* pBlackboard, const float elapsedSeconds);
		void LateUpdate(Blackboard* pBlackboard, const float elapsedSeconds);

	private:
		FSMStateChangeCallback m_FSMStateChangeCallback;
		FSMStateUpdateCallback m_FSMStateFixedUpdateCallback;
		FSMStateUpdateCallback m_FSMStateUpdateCallback;
		FSMStateUpdateCallback m_FSMStateLateUpdateCallback;
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
		FiniteStateMachineComponent(GameObject* pParent, std::shared_ptr<FSMState> pStartState, Blackboard* pBlackboard);
		~FiniteStateMachineComponent();

		void AddTransition(std::shared_ptr<FSMState> pFromState, std::shared_ptr<FSMState> pToState, std::shared_ptr<FSMTransition> pTransition);

		virtual void Update(const float elapsedSeconds) override;

		Blackboard* GetBlackboard() const noexcept;
		FSMState* GetCurrentState() const noexcept;

	private:
		void ChangeState(const std::shared_ptr<FSMState>& pFSMState);

		Blackboard* m_pBlackboard;

		// https://stackoverflow.com/questions/4437862/whats-the-advantage-of-multimap-over-map-of-vectors
		using StateTransitionPair = std::pair<std::shared_ptr<FSMTransition>, std::shared_ptr<FSMState>>;
		using StatePair = std::pair<std::shared_ptr<FSMState>, std::vector<StateTransitionPair>>;

		std::unordered_map<std::shared_ptr<FSMState>, std::vector<StateTransitionPair>> m_pStates;
		std::shared_ptr<FSMState> m_pCurrentState;
	};
}


#endif // !INTEGRIAN_FINITESTATEMACHINE_H