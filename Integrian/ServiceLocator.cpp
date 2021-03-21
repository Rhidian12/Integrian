#include "pch.h"
#include "ServiceLocator.h"

Integrian::ServiceLocator::~ServiceLocator()
{
	for (IService* pService : m_pServices)
		SafeDelete(pService);

	SafeDelete(m_pNullService);
}
