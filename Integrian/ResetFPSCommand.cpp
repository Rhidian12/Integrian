#include "ResetFPSCommand.h"
#include "FPSComponent.h"

Integrian::ResetFPSCommand::ResetFPSCommand(FPSComponent* pFPSComponent)
	: Command{}
	, m_pFPSComponent{ pFPSComponent }
{
}

void Integrian::ResetFPSCommand::Execute()
{
	std::cout << "TEST" << std::endl;
}
