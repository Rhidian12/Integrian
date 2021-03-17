#include "ActorComponent.h"
#include "InputManager.h"
#include "Subject.h"

Integrian::ActorComponent::ActorComponent()
	: m_pSubject{ std::make_unique<Subject>() }
{
}

void Integrian::ActorComponent::Invoke(const std::string& event)
{
	m_pSubject->Notify(event);
}