#include "KillCommand.h"
#include "HealthComponent.h"
#include "EventQueue.h"

Integrian::KillCommand::KillCommand(HealthComponent* pHealth)
	: m_pHealthComponent{ pHealth }
{
}

void Integrian::KillCommand::Execute()
{
	m_pHealthComponent->DecreaseLivesByValue(1);
	EventQueue::GetInstance().QueueEvent(Event{ "PlaySound", 0, false, 0, 100 });
}
