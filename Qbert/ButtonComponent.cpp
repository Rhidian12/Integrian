#include "ButtonComponent.h"
#include <InputManager.h>
#include <EventQueue.h>

ButtonComponent::ButtonComponent(Integrian::GameObject* pParent, const std::string& event)
	: Component{ pParent }
	, m_Event{ event }
	, m_IsSelected{}
{
}

void ButtonComponent::PostInitialize()
{
	using namespace Integrian;

	InputManager::GetInstance().AddCommand(GameInput{ KeyboardInput::Enter }, [this]()
		{
			if (!m_IsSelected)
				return;

			EventQueue::GetInstance().QueueEvent(Event{ m_Event });
		}, State::OnRelease);

	InputManager::GetInstance().AddCommand(GameInput{ ControllerInput::ButtonA }, [this]()
		{
			if (!m_IsSelected)
				return;

			EventQueue::GetInstance().QueueEvent(Event{ m_Event });
		}, State::OnRelease);
}

void ButtonComponent::SetIsSelected(bool isSelected)
{
	m_IsSelected = isSelected;
}

const bool ButtonComponent::GetIsSelected() const noexcept
{
	return m_IsSelected;
}
