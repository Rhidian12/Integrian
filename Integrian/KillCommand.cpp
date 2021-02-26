#include "KillCommand.h"
#include "HealthComponent.h"

Integrian::KillCommand::KillCommand(HealthComponent* pHealth)
	: m_pHealthComponent{ pHealth }
{
}

void Integrian::KillCommand::Execute()
{
	m_pHealthComponent->DecreaseLivesByValue(1);
}
