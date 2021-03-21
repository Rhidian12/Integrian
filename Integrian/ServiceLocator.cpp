#include "pch.h"
#include "ServiceLocator.h"

Integrian::ServiceLocator::ServiceLocator()
{
	m_pNullService = new NullService{};
}

Integrian::ServiceLocator::~ServiceLocator()
{
	for (IService* pService : m_pServices)
		SafeDelete(pService);

	SafeDelete(m_pNullService);
}
