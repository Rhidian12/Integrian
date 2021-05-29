#pragma once

#ifndef INTEGRIAN_FINITESTATEMACHINE_H
#define INTEGRIAN_FINITESTATEMACHINE_H

#include "Component.h"
#include "Blackboard.h"

namespace Integrian
{
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

		void OnStateChange(Blackboard* pBlackboard);
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


	private:

	};
}


#endif // !INTEGRIAN_FINITESTATEMACHINE_H