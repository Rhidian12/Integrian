#include "pch.h"
#include "ServiceLocator.h"

void Integrian::ServiceLocator::Cleanup()
{
	for (IService* pService : m_pServices)
		SafeDelete(pService);

	SafeDelete(m_pNullService);
}
