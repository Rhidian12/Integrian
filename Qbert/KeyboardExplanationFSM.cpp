#include "KeyboardExplanationFSM.h"

#include <Blackboard.h>
#include <FiniteStateMachine.h>
#include <App.h>
#include <App_Selector.h>
#include "Qbert_MainGame.h"
#include <InputManager.h>

KeyboardExplanationFSM::KeyboardExplanationFSM(Integrian::GameObject* pParent)
	: Component{ pParent }
	, m_pBlackboard{ new Integrian::Blackboard{} }
	, m_SelectedKeyboardInputs{}
{
}

void KeyboardExplanationFSM::PostInitialize()
{
	using namespace Integrian;

	App* pActiveApp{ App_Selector::GetInstance().GetActiveApplication() };

	for (const std::pair<GameObjectInformation, GameObject*>& pair : pActiveApp->GetGameObjects())
		if (pair.second->GetTag() == "Text")
			m_pTextComponents.insert(std::make_pair(pair.first.m_Identifier, pair.second));
}

void KeyboardExplanationFSM::Update(const float)
{
	using namespace Integrian;

	if (m_pBlackboard->GetData<bool>("LeftTopKeybindSet"))
	{
		App_Selector::GetInstance().SetActiveApplication("Qbert_MainGame" + std::to_string(Qbert_MainGame::GetLevel()));
	}
}

Integrian::FiniteStateMachineComponent* KeyboardExplanationFSM::CreateKeyboardFSM() noexcept
{
	using namespace Integrian;

	m_pBlackboard->AddData("RightTopKeybindSet", false);
	m_pBlackboard->AddData("RightBottomKeybindSet", false);
	m_pBlackboard->AddData("LeftTopKeybindSet", false);
	m_pBlackboard->AddData("LeftBottomKeybindSet", false);

	std::shared_ptr<FSMState> rightTopState{ new FSMState{
	[this](Blackboard*, FSMStateTransition transition)
		{
			if (transition == FSMStateTransition::OnExit)
			{
				SDL_PumpEvents();
				m_pTextComponents.find("RightTopText")->second->SetIsActive(false);
			}
		},
	[](Blackboard*, const float) {},
	[this](Blackboard* pBlackboard, const float)
		{
			const KeyboardInput pressedKey{ InputManager::GetInstance().GetWhichKeyIsPressed() };
			if (pressedKey != KeyboardInput::INVALID)
			{
				EventQueue::GetInstance().QueueEvent(Event{"RightTopKeybind", pressedKey});
				pBlackboard->ChangeData("RightTopKeybindSet", true);
				m_SelectedKeyboardInputs.push_back(pressedKey);
			}
		}
	} };

	std::shared_ptr<FSMTransition> toRightBottom{ new FSMTransition{
	[this](Blackboard* pBlackboard)->bool
		{
			return pBlackboard->GetData<bool>("RightTopKeybindSet");
		}} };

	std::shared_ptr<FSMState> rightBottomState{ new FSMState{
	[this](Blackboard*, FSMStateTransition transition)
		{
			if (transition == FSMStateTransition::OnEnter)
			{
				InputManager::GetInstance().ResetInputs();
				m_pTextComponents.find("RightBottomText")->second->SetIsActive(true);
			}
			else
			{
				SDL_PumpEvents();
				m_pTextComponents.find("RightBottomText")->second->SetIsActive(false);
			}
		},
	[](Blackboard*, const float) {},
	[this](Blackboard* pBlackboard, const float)
	{
		const KeyboardInput pressedKey{ InputManager::GetInstance().GetWhichKeyIsPressed() };
		if (pressedKey != KeyboardInput::INVALID)
		{
			const std::vector<KeyboardInput>::const_iterator cIt{ std::find(m_SelectedKeyboardInputs.cbegin(), m_SelectedKeyboardInputs.cend(), pressedKey) };

			if (cIt == m_SelectedKeyboardInputs.cend())
			{
				EventQueue::GetInstance().QueueEvent(Event{"RightBottomKeybind", pressedKey});
				pBlackboard->ChangeData("RightBottomKeybindSet", true);
				m_SelectedKeyboardInputs.push_back(pressedKey);
			}
		}
	}
} };

	std::shared_ptr<FSMTransition> toLeftBottom{ new FSMTransition{
	[this](Blackboard* pBlackboard)->bool
	{
		return pBlackboard->GetData<bool>("RightBottomKeybindSet");
	}} };

	std::shared_ptr<FSMState> leftBottomState{ new FSMState{
	[this](Blackboard*, FSMStateTransition transition)
		{
			if (transition == FSMStateTransition::OnEnter)
			{
				InputManager::GetInstance().ResetInputs();
				m_pTextComponents.find("LeftBottomText")->second->SetIsActive(true);
			}
			else
			{
				SDL_PumpEvents();
				m_pTextComponents.find("LeftBottomText")->second->SetIsActive(false);
			}
		},
	[](Blackboard*, const float) {},
	[this](Blackboard* pBlackboard, const float)
	{
		const KeyboardInput pressedKey{ InputManager::GetInstance().GetWhichKeyIsPressed() };
		if (pressedKey != KeyboardInput::INVALID)
		{
			const std::vector<KeyboardInput>::const_iterator cIt{ std::find(m_SelectedKeyboardInputs.cbegin(), m_SelectedKeyboardInputs.cend(), pressedKey) };

			if (cIt == m_SelectedKeyboardInputs.cend())
			{
				EventQueue::GetInstance().QueueEvent(Event{"LeftBottomKeybind", pressedKey});
				pBlackboard->ChangeData("LeftBottomKeybindSet", true);
				m_SelectedKeyboardInputs.push_back(pressedKey);
			}
		}
	}
} };

	std::shared_ptr<FSMTransition> toLeftTop{ new FSMTransition{
	[this](Blackboard* pBlackboard)->bool
	{
		return pBlackboard->GetData<bool>("LeftBottomKeybindSet");
	}} };

	std::shared_ptr<FSMState> leftTopState{ new FSMState{
	[this](Blackboard*, FSMStateTransition transition)
		{
			if (transition == FSMStateTransition::OnEnter)
			{
				InputManager::GetInstance().ResetInputs();
				m_pTextComponents.find("LeftTopText")->second->SetIsActive(true);
			}
			else
			{
				SDL_PumpEvents();
				m_pTextComponents.find("LeftTopText")->second->SetIsActive(false);
			}
		},
	[](Blackboard*, const float) {},
	[this](Blackboard* pBlackboard, const float)
	{
		const KeyboardInput pressedKey{ InputManager::GetInstance().GetWhichKeyIsPressed() };
		if (pressedKey != KeyboardInput::INVALID)
		{
			const std::vector<KeyboardInput>::const_iterator cIt{ std::find(m_SelectedKeyboardInputs.cbegin(), m_SelectedKeyboardInputs.cend(), pressedKey) };

			if (cIt == m_SelectedKeyboardInputs.cend())
			{
				EventQueue::GetInstance().QueueEvent(Event{"LeftTopKeybind", pressedKey});
				pBlackboard->ChangeData("LeftTopKeybindSet", true);
				m_SelectedKeyboardInputs.push_back(pressedKey);
			}
		}
	}
} };

	FiniteStateMachineComponent* pFSM{ new FiniteStateMachineComponent{m_pParent, rightTopState, m_pBlackboard} };
	pFSM->AddTransition(rightTopState, rightBottomState, toRightBottom);
	pFSM->AddTransition(rightBottomState, leftBottomState, toLeftBottom);
	pFSM->AddTransition(leftBottomState, leftTopState, toLeftTop);

	return pFSM;
}
