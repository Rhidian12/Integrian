#include "KillCommand.h" // Header
#include "HealthComponent.h" // HealthComponent
#include "AppInfoLocator.h" // AppInfoLocator, also includes

Integrian::KillCommand::KillCommand(HealthComponent* pHealth)
	: m_pHealthComponent{ pHealth }
{
}

void Integrian::KillCommand::Execute()
{
	m_pHealthComponent->DecreaseLivesByValue(1);
	AppInfoLocator::GetAppInfo()->eventQueue.QueueEvent(Event{ "PlaySound", 0, false, 0, 100 });
}
