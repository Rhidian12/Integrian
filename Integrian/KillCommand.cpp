#include "KillCommand.h"
#include "ActorComponent.h"

Integrian::KillCommand::KillCommand(ActorComponent* pActor)
	: m_pActor{ pActor }
{
}

void Integrian::KillCommand::Execute()
{
	m_pActor->Invoke("Kill");
}
