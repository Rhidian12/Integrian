#include "TestCommand.h"
#include "FPSComponent.h"

Integrian::TestCommand::TestCommand(FPSComponent* pFPSComponent)
	: Command{}
	, m_pFPSComponent{ pFPSComponent }
{
}

void Integrian::TestCommand::Execute()
{
	std::cout << "TEST" << std::endl;
}
