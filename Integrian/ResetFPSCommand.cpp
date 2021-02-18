#include "ResetFPSCommand.h"
#include "FPSComponent.h"

Integrian::ResetFPSCommand::ResetFPSCommand(FPSComponent* pFPSComponent, const GameObject& actor)
	: Command{ actor }
	, m_pFPSComponent{ pFPSComponent }
{
}

void Integrian::ResetFPSCommand::Execute()
{
	m_pFPSComponent->SetFPS(666);
}
