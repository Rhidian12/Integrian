#include "ActorComponent.h"
#include "InputManager.h"
#include "Subject.h"

Integrian::ActorComponent::ActorComponent()
	: m_pSubject{ std::make_unique<Subject>() }
{
}

void Integrian::ActorComponent::AddCommand(const GameInput& gameInput, Command* pCommand, const State keyState, const uint8_t controllerIndex)
{
	InputManager::GetInstance().AddCommand(gameInput, pCommand, keyState, controllerIndex);
}

void Integrian::ActorComponent::AddObserver(std::weak_ptr<Observer> pObserver)
{
	m_pSubject->AddObserver(pObserver);
}

void Integrian::ActorComponent::Invoke(const std::string& event)
{
	m_pSubject->Notify(event);
}